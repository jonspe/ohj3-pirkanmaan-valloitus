
local Hex = require("hex")
local Color = require("color")
local CSV = require("csv")



local Terrain = {}

--[[
	Creates Terrain data from a terrain image, reads data from it
]]
function Terrain.new()
	local self = setmetatable({}, {__index = Terrain})
	
	self.width = 0
	self.height = 0
	self.data = {}
	
	self.gDict = {}
	self.bDict = {}
	self.spritePositions = {}
	
	return self
end


function Terrain:loadMetadata(dataPath)
	local csv = CSV.readCsvFile(dataPath)
	for row = 3, #csv do
		local cols = csv[row]
		
		local id = cols[1]
		local sprite_x = tonumber(cols[2])
		local sprite_y = tonumber(cols[3])
		local channel_g = tonumber(cols[7])
		local channel_b = tonumber(cols[8])
		
		if channel_g then
			self.gDict[channel_g] = id
		end
		
		if channel_b then
			self.bDict[channel_b] = id
		end
		
		self.spritePositions[id] = {x = sprite_x, y = sprite_y}
	end
end

function Terrain:loadTerrainData(dataPath)
	local imageData = love.image.newImageData(dataPath)
	local width, height = imageData:getDimensions()
	self.width = width
	self.height = height
	
	-- Reads pixel from terrain image and converts it to a Hex object
	local function pixelToHex(x, y, r, g, b, a)
		local height = r -- TERRAIN HEIGHT
		local objId = self.gDict[math.floor(g*255)] -- FEATURE ID
		local hexId = self.bDict[math.floor(b*255)] -- HEX ID
		local color = a -- HEX COLOR
		
		if height*255 < 1 then -- WATER THRESHOLD
			hexId = "HEX_WATER"
		end
		
		if objId == nil then -- Empty sprite if invalid rgb value
			objId = "NONE"
		end
		
		if hexId == nil then -- Empty sprite if invalid rgb value
			hexId = "NONE"
		end
		
		local hex = Hex.new(x, y, height, hexId, objId, color)
		return hex
	end

	-- Read data from terrain image
	for y = 0, height-1 do
		if self.data[y] == nil then
			self.data[y] = {}
		end
		
		for x = 0, width-1 do
			self.data[y][x] = pixelToHex(x, y, imageData:getPixel(x,y))
		end
	end
end

function Terrain:loadTextureAtlas(imagePath, divisions)
	self.textureAtlas = love.graphics.newImage(imagePath)
	self.spriteBatch = love.graphics.newSpriteBatch(self.textureAtlas, 10000)
	
	local width, height = self.textureAtlas:getDimensions() -- eh should be a power of 2 square i guess
	local size = width/divisions
	
	local function quad(x, y)
		return love.graphics.newQuad(x*size, y*size, size, size, width, height)
	end
	
	-- Divide spritesheet into squares
	self.spriteQuads = {}
	
	for id, pos in pairs(self.spritePositions) do
		self.spriteQuads[id] = quad(pos.x, pos.y)
	end
end


local function step(x, base)
	return base * math.floor(x/base)
end

--[[
	Creates quads from hex data to sprite batch
	Run only once when generating terrain
]]
function Terrain:populateSprites()
	for y = 0, self.height-1 do
		local oddx = y%2 == 1 and 128 or 0 -- Align hexes horizontally, lock into slots
		for x = 0, self.width-1 do
			local hex = self.data[y][x]
			local hexQuad = self.spriteQuads[hex.hexId]
			local objQuad = self.spriteQuads[hex.objId]
			
			self.spriteBatch:setColor(Color.hslToRgb(step(hex.color*11, 0.02)%1, 1, 0.987))
			self.spriteBatch:add(hexQuad, hex.x * 256 + oddx, hex.y * 120 - hex.height * 8 * 42)
			
			--self.spriteBatch:setColor(1, 1, 1) -- Keep hex object as is
			self.spriteBatch:add(objQuad, hex.x * 256 + oddx, hex.y * 120 - 90 - hex.height * 8 *  42)
		end
	end
end

--[[
	Draw the quads in the SpriteBatch
]]
function Terrain:draw()
	love.graphics.draw(self.spriteBatch, 0, 0)
end



return Terrain
