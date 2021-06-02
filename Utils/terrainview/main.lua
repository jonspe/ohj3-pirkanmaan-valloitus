
local Terrain = require("terrain")

-- Ugly global variables here
local currentTerrain
local mapX, mapY = 0, 0
local zoom = 1
local mouseDown = false

local terrainDir = "src/terrain/"
local terrainList = {}
local terrainIndex = 1


local function loadTerrain(index)
	if currentTerrain then
		currentTerrain.spriteBatch:clear()
		currentTerrain = nil
	end
	
	currentTerrain = Terrain.new()
	currentTerrain:loadMetadata("src/terrain_metadata.csv")
	currentTerrain:loadTerrainData(terrainDir .. terrainList[index])
	currentTerrain:loadTextureAtlas("src/sprites/sprites.png", 8)
	currentTerrain:populateSprites()
end

function love.load()
	-- Make sprites not look like complete ass in the borders
	love.graphics.setDefaultFilter("nearest", "nearest", 0)
	
	-- List all terrain images in folder to this array
	terrainList = love.filesystem.getDirectoryItems(terrainDir)
	
	-- Load terrain at index, index is determined by file system somehow, so assume random order
	loadTerrain(terrainIndex)
end

function love.mousemoved(x, y, dx, dy)
	-- If dragging then move map by mouse delta
	if mouseDown then
		mapX = mapX + dx*(1/zoom)
		mapY = mapY + dy*(1/zoom)
	end
end

function love.mousepressed()
	mouseDown = true
end

function love.mousereleased()
	mouseDown = false
end

function love.keypressed(key)
	-- Switch terrains
	if key == "left" then
		terrainIndex = terrainIndex - 1
	elseif key == "right" then
		terrainIndex = terrainIndex + 1
	end
	
	terrainIndex = (terrainIndex-1) % #terrainList + 1
	loadTerrain(terrainIndex)
end

function love.wheelmoved(x, y)
	if y == -1 then
		zoom = zoom/2
	elseif y == 1 then
		zoom = zoom*2
	end
end

function love.update()
end

function love.draw()
	local width, height = love.graphics.getDimensions()
	
	love.graphics.translate(width/2, height/2)
	love.graphics.scale(zoom, zoom)
	love.graphics.translate(mapX, mapY)
	
	-- Draw the terrain 60fps
	currentTerrain:draw()
end
