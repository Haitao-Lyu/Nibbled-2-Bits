local path = "./" -- directory path, change this to the desired path
local extension = ".png" -- file extension to filter by, change this to the desired extension
local output_filename = "file_list.txt" -- output filename, change this to the desired filename

-- open output file for writing
local output_file = io.open(output_filename, "w")

-- loop through all files in directory
for file in io.popen('ls "'..path..'"'..extension):lines() do
    -- extract filename without extension
    local filename = string.match(file, "(.+)%..+")
    -- write filename to output file
    output_file:write(filename.."\n")
end

-- close output file
output_file:close()
