
local Hex = {}

function Hex.new(x, y, height, hexId, objId, color)
	local self = setmetatable({}, {__index = Hex})
	self.x = x
	self.y = y
	
	self.height = height
	self.color = color
	
	self.hexId = hexId
	self.objId = objId
	
	return self
end

return Hex