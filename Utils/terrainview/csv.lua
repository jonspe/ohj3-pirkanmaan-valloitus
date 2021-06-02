
local delim = ";"

-- Convert from CSV string to table (converts a single line of a CSV file)
local function fromCSV (s)
  s = s .. delim       -- ending comma
  local t = {}        -- table to collect fields
  local fieldstart = 1
  repeat
    -- next field is quoted? (start with `"'?)
    if string.find(s, '^"', fieldstart) then
      local a, c
      local i  = fieldstart
      repeat
        -- find closing quote
        a, i, c = string.find(s, '"("?)', i+1)
      until c ~= '"'    -- quote not followed by quote?
      if not i then error('unmatched "') end
      local f = string.sub(s, fieldstart+1, i-1)
      table.insert(t, (string.gsub(f, '""', '"')))
      fieldstart = string.find(s, delim, i) + 1
    else                -- unquoted; find next comma
      local nexti = string.find(s, delim, fieldstart)
      table.insert(t, string.sub(s, fieldstart, nexti-1))
      fieldstart = nexti + 1
    end
  until fieldstart > string.len(s)
  return t
end

local function readCsvFile(path)
	local fileString = love.filesystem.read(path)
	
	local rows = {}
	for line in fileString:gmatch("[^\r\n]+") do
		table.insert(rows, fromCSV(line))
	end
	
	return rows
end


return
{
	readCsvFile = readCsvFile
}