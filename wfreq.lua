local argparse = require "argparse"

version = "1.0"

progs = {"Lab_4.4/out/Lab_4.4", "Pygram/pygram.py"}

function pt(table)
	for k, v in pairs(table) do
		print(k, v)
		if type(v) == type({}) then
			for i, j in pairs(v) do
				print("\t", i, j)
			end
		end
	end
end

function pipeclose(pipe, prog, output)
	ret = table.pack(pipe:close())

	if ret[1] == nil then
		io.stderr:write("Error: ./", prog, " exited with signal ",ret[3], " with output:\n", output or "")
		os.exit(1)
	end
end


local parser = argparse()
:name "wfreq"
:description "Linkage script beetween Lab_4.4 and Pygram."
:help_max_width(80)
:epilog [[
Typical format:
  $ wfreq <wfreq.lua options> [-- <pygram.py options>]
Where:
   <wfreq.lua options> Are shown above.
   <pygram.py options> You can check them with
                       $ python3 Pygram/pygram.py --help

Example usage:
  $ lua wfreq.lua -f hamlet.txt -m 20 -- --title "Words" --rotation 90 
    --label -x "Words" -y "Quantity"
]]

parser:argument("pygram")
:args "*"

parser:option "--max -m"
:description "Max word count returned from Lab 4.4. Also the max bars to be shown in Pygram."
:argname "NUM"
:default(math.huge)
:convert(function(num)
	n, msg = tonumber(num)

	if type(n) == nil then
		return n, msg
	end
	
	if n == 0 then 
		return nil, "You set have set --max to 0. You will see no output."
	elseif n < 0 then
		return nil, "--max can't be negative."
	end
	return n
end)

parser:option "--file -f"
:description "Input text file."
:argname("FILE")
:args(1)
:count(1)
:convert(function(fname)
	s, msg = io.open(fname)
	if type(s) == nil then
		return s, msg
	end
	return fname
end)

parser:flag "--version -v"
:description "Print version and exit."
:action(function()
	io.write("Version v", version, ".\n")
end)

local args = parser:parse()

local _  = {}
for i = 1, #progs do
	_[i] = table.pack(io.open(progs[i]))
end

for i = 1, #_ do
	if _[i][1] == nil then
		io.stderr:write("Error: could not open : ", _[i][2], "\n")
		os.exit(1)
	end
end
_ = nil


local lab4 = io.popen("./" .. progs[1] .. " -s 1 -f " .. args.file .. " -m " .. args.max)
local words = lab4:read("all")

pipeclose(lab4, progs[1], words)

local dataname = os.tmpname()
print(dataname)
local file = io.open(dataname, "w") 
file:write(words)
file:close()
words = nil

local pygram_opts = ""

for i, j in pairs(args.pygram) do
	pygram_opts = pygram_opts .. " " .. j
end

local pygram = io.popen("python3 " .. progs[2] .. " --file " .. dataname .. pygram_opts)
local pyout = pygram:read("all")
pipeclose(pygram, progs[2], pyout)
pyout = nil
dataname = nil
pygram_opts = nil


io.output(io.stdout)
