# TERRAIN AND FEATURE GENERATOR
#
# generates randomized terrain data based on perlin noise
# stores data in an image using pixel color values
#
# R = heightmap
# G = tile features
# B = biome data
# A = hex color variation
#
# HOW TO USE:
#   1. install PIL and noise libraries
#   2. set correct path in FILE_LOCATION (folder must already exist)
#   3. run script

from PIL import Image
import noise
import random


FILENAME = str(random.randrange(1, 100000))
FILE_LOCATION = 'C:/Users/Joona/Desktop/pirkanmaa_project/terrainview/src/terrain/' + FILENAME + '.png'

MAP_SIZE_X = 100  # technically supports up to 99999x99999, python runs out of memory around 4000x4000
MAP_SIZE_Y = MAP_SIZE_X

Z_AVERAGE_COUNT = 1  # increase for rounder elevation borders
DESERT_AVERAGE_COUNT = 4  # increase for rounder desert
TEMP_AVERAGE_COUNT = 4  # increase for "realistic" temperature generation; keep above 1

Z_MULTIPLIER = 1 + random.randrange(-100, 100) / 10000  # multiplies post-noise z value

Y_COORD_START = random.randint(-500, 500)  # randomizes noise start location; larger numbers for more variety
X_COORD_START = random.randint(-500, 500)  # randomizes noise start location; larger numbers for more variety

TEMP_NOISE_AMOUNT = random.randrange(50, 65)  # high values for higher temperature variance

DESERT_TEMP = 100  # temp above which desert is generated

# TILE HEIGHT VALUES
SEA_LEVEL = -0.14  # everything below this is water
ELEV_1 = SEA_LEVEL + 0.11
ELEV_2 = SEA_LEVEL + 0.22
ELEV_3 = SEA_LEVEL + 0.33
ELEV_4 = SEA_LEVEL + 0.50

# NOISE SPAWN VALUES
FOREST_SPAWN_VALUE = 0.07  # decrease to spawn more forest
STONE_SPAWN_VALUE = 0.17  # decrease to spawn more stone
BIOME_SPAWN_VALUE = 0  # do not mess with this
TERRAIN_SPAWN_VALUE = 0  # do not mess with this

# HEIGHT NOISE SETTINGS
Z_RANDOM_MULTIPLIER = random.randrange(90, 110) / 100
Z_NOISE_X = 40
Z_NOISE_Y = 40
Z_OCTAVES = 7
Z_PERSISTENCE = 0.535 * Z_RANDOM_MULTIPLIER
Z_LACUNARITY = 2.15
Z_REPEAT_X = MAP_SIZE_X
Z_REPEAT_Y = MAP_SIZE_Y
Z_BASE = random.randint(-100, 200)

# FOREST NOISE SETTINGS
F_NOISE_X = 30
F_NOISE_Y = 30
F_OCTAVES = 11
F_PERSISTENCE = 0.8
F_LACUNARITY = 2
F_REPEAT_X = random.randrange(500, 50000)
F_REPEAT_Y = random.randrange(500, 50000)
F_BASE = random.randint(-12, 12)

# BIOME NOISE SETTINGS
B_NOISE_X = 30
B_NOISE_Y = 30
B_OCTAVES = 4
B_PERSISTENCE = 0.5
B_LACUNARITY = 2
B_REPEAT_X = random.randrange(500, 50000)
B_REPEAT_Y = random.randrange(500, 50000)
B_BASE = random.randint(-12, 12)

# TEMPERATURE NOISE SETTINGS
T_NOISE_X = 25
T_NOISE_Y = 25
T_OCTAVES = 40
T_PERSISTENCE = 0.9
T_LACUNARITY = 2
T_REPEAT_X = random.randrange(500, 50000)
T_REPEAT_Y = random.randrange(500, 50000)
T_BASE = random.randint(0, 30)

# STONE NOISE SETTINGS
S_NOISE_X = 6
S_NOISE_Y = 6
S_OCTAVES = 30
S_PERSISTENCE = 0.6
S_LACUNARITY = 4
S_REPEAT_X = random.randrange(500, 50000)
S_REPEAT_Y = random.randrange(500, 50000)
S_BASE = random.randint(0, 30)

# DESERT NOISE SETTINGS
D_NOISE_X = 10
D_NOISE_Y = 10
D_OCTAVES = 20
D_PERSISTENCE = 0.6
D_LACUNARITY = 2
D_REPEAT_X = random.randrange(500, 50000)
D_REPEAT_Y = random.randrange(500, 50000)
D_BASE = random.randint(0, 30)


def main():
    tile_ids = []
    tiles = {}

    print("Generating map...")

    for x in range(MAP_SIZE_X + 1):
        for y in range(MAP_SIZE_Y + 1):
            z = noise.pnoise2((x + X_COORD_START) / Z_NOISE_X, (y + Y_COORD_START) / Z_NOISE_Y, octaves=Z_OCTAVES,
                              persistence=Z_PERSISTENCE, lacunarity=Z_LACUNARITY,
                              repeatx=Z_REPEAT_X * random.randint(1, 6), repeaty=Z_REPEAT_Y * random.randint(1, 6),
                              base=Z_BASE)
            z = z * Z_MULTIPLIER

            evergreen_forest = noise.pnoise2((x + X_COORD_START) / F_NOISE_X, (y + Y_COORD_START) / F_NOISE_Y,
                                        octaves=F_OCTAVES,
                                        persistence=F_PERSISTENCE, lacunarity=F_LACUNARITY,
                                        repeatx=F_REPEAT_X, repeaty=F_REPEAT_Y, base=F_BASE)

            birch_forest = noise.pnoise2((x + X_COORD_START) / F_NOISE_X * 0.9, (y + Y_COORD_START) / F_NOISE_Y * 1.1,
                                         octaves=F_OCTAVES + 1,
                                         persistence=0.9, lacunarity=F_LACUNARITY * 0.99,
                                         repeatx=F_REPEAT_X + 120, repeaty=F_REPEAT_Y + 500, base=F_BASE + 2)

            biome = noise.pnoise2((x + X_COORD_START) / B_NOISE_X, (y + Y_COORD_START) / B_NOISE_Y,
                                         octaves=10,
                                         persistence=2, lacunarity=B_LACUNARITY * 0.99,
                                         repeatx=B_REPEAT_X + 420, repeaty=B_REPEAT_Y  +300, base=F_BASE + 5)

            terrain = noise.pnoise2((x + X_COORD_START) / T_NOISE_X, (y + Y_COORD_START) / T_NOISE_Y,
                                        octaves=T_OCTAVES,
                                        persistence=T_PERSISTENCE, lacunarity=T_LACUNARITY,
                                        repeatx=T_REPEAT_X, repeaty=T_REPEAT_Y, base=T_BASE)

            old_terrain_range = (0.25 + 0.25)
            new_terrain_range = 255
            terrain = - ((((terrain + 0.25) * new_terrain_range) / old_terrain_range) + 0)

            stone = noise.pnoise2((x + X_COORD_START) / S_NOISE_X, (y + Y_COORD_START) / S_NOISE_Y,
                                        octaves=S_OCTAVES,
                                        persistence=S_PERSISTENCE, lacunarity=S_LACUNARITY,
                                        repeatx=S_REPEAT_X, repeaty=S_REPEAT_Y, base=S_BASE)

            temp = (y - MAP_SIZE_Y / 2)

            temp_noise = noise.pnoise2(x / Z_NOISE_X, y / F_NOISE_X, octaves=30, persistence=0.9, lacunarity=2.0,
                                       repeatx=1024, repeaty=1024, base=F_BASE)
            temp = temp + TEMP_NOISE_AMOUNT * temp_noise  # required for more realistic edges

            # temp is completely arbitrarily scaled
            # messing with this requires DESERT_TEMP and SNOW_TEMP to be rebalanced
            old_temp_range = (-MAP_SIZE_Y - 0)
            new_temp_range = (30 - (-140))
            scaled_temp = - ((((temp - 0) * new_temp_range) / old_temp_range) - 40) + random.randrange(-2, 2)

            scaled_temp = scaled_temp + temp_noise * TEMP_NOISE_AMOUNT

            desert = noise.pnoise2(x / D_NOISE_X, y / D_NOISE_Y, octaves=D_OCTAVES,
                                   persistence=D_PERSISTENCE, lacunarity=D_LACUNARITY,
                                   repeatx=D_REPEAT_X, repeaty=D_REPEAT_Y, base=D_BASE)

            new_tile = Tile(x, y, z, evergreen_forest, birch_forest, biome, terrain, stone, desert, scaled_temp)
            string_x = str(x)
            string_y = str(y)
            # key format 000000x00000y
            tile_id = str(string_x.zfill(5)) + "x" + str(string_y.zfill(5)) + "y"

            tile_ids.append(tile_id)
            tiles[tile_id] = new_tile

        x = x + 1
        if x == MAP_SIZE_X / 4:
            print("Generation 25% complete")
        elif x == MAP_SIZE_X / 2:
            print("Generation 50% complete")
        elif x == MAP_SIZE_X * 0.75:
            print("Generation 75% complete")
        elif x == MAP_SIZE_X:
            print("Generation 100% complete")

        i = 1

    print("Averaging height...")
    i = 1
    while i != Z_AVERAGE_COUNT + 1:
        average(tiles, tile_ids, "z")
        print("Height average", i, "of", Z_AVERAGE_COUNT, "complete")
        i = i + 1

    print("Averaging temperature...")
    i = 1
    while i != TEMP_AVERAGE_COUNT + 1:
        average(tiles, tile_ids, "temp")
        print("Temperature average", i, "of", TEMP_AVERAGE_COUNT, "complete")
        i = i + 1

    print("Averaging desert...")
    i = 1
    while i != DESERT_AVERAGE_COUNT + 1:
        average(tiles, tile_ids, "desert")
        print("Desert average", i, "of", DESERT_AVERAGE_COUNT, "complete")
        i = i + 1

    draw(tiles, tile_ids, )


def average(tiles, tile_ids, target):
    averages = {}
    for tile_id in tile_ids:
        nearby_tile_ids = []

        x = tiles[tile_id].get_x()
        y = tiles[tile_id].get_y()

        xplus = False
        xminus = False
        yplus = False
        yminus = False

        if x + 1 < MAP_SIZE_X:
            string_x_plus = str(x + 1)
            xplus = True
        if x - 1 > 0:
            string_x_minus = str(x - 1)
            xminus = True
        if y + 1 < MAP_SIZE_Y:
            string_y_plus = str(y + 1)
            yplus = True
        if y - 1 > 0:
            yminus = True
            string_y_minus = str(y - 1)

        string_x = str(x)
        string_y = str(y)

        if xplus:
            if yplus:
                nearby_tile_id_1 = str(string_x_plus.zfill(5)) + "x" + str(string_y_plus.zfill(5)) + "y"
                nearby_tile_ids.append(nearby_tile_id_1)
            if yminus:
                nearby_tile_id_3 = str(string_x_plus.zfill(5)) + "x" + str(string_y_minus.zfill(5)) + "y"
                nearby_tile_ids.append(nearby_tile_id_3)
            nearby_tile_id_2 = str(string_x_plus.zfill(5)) + "x" + str(string_y.zfill(5)) + "y"
            nearby_tile_ids.append(nearby_tile_id_2)

        if yplus:
            nearby_tile_id_4 = str(string_x.zfill(5)) + "x" + str(string_y_plus.zfill(5)) + "y"
            nearby_tile_ids.append(nearby_tile_id_4)
        if yminus:
            nearby_tile_id_6 = str(string_x.zfill(5)) + "x" + str(string_y_minus.zfill(5)) + "y"
            nearby_tile_ids.append(nearby_tile_id_6)
        nearby_tile_id_5 = str(string_x.zfill(5)) + "x" + str(string_y.zfill(5)) + "y"
        nearby_tile_ids.append(nearby_tile_id_5)

        if xminus:
            if yplus:
                nearby_tile_id_7 = str(string_x_minus.zfill(5)) + "x" + str(string_y_plus.zfill(5)) + "y"
                nearby_tile_ids.append(nearby_tile_id_7)
            if yminus:
                nearby_tile_id_9 = str(string_x_minus.zfill(5)) + "x" + str(string_y_minus.zfill(5)) + "y"
                nearby_tile_ids.append(nearby_tile_id_9)
            nearby_tile_id_8 = str(string_x_minus.zfill(5)) + "x" + str(string_y.zfill(5)) + "y"
            nearby_tile_ids.append(nearby_tile_id_8)

        sum = 0
        for nearby_tile_id in nearby_tile_ids:
            if target == "temp":
                sum += tiles[nearby_tile_id].get_temp()
            elif target == "desert":
                sum += tiles[nearby_tile_id].get_desert()
            elif target == "z":
                sum += tiles[nearby_tile_id].get_z()
        averages[tile_id] = sum / len(nearby_tile_ids)

    for tile_id in tile_ids:
        new = averages[tile_id]
        if target == "temp":
            tiles[tile_id].mod_temp(new)
        elif target == "desert":
            tiles[tile_id].mod_desert(new)
        elif target == "z":
            tiles[tile_id].mod_z(new)


class Tile:

    def __init__(self, x, y, z, evergreen_forest, birch_forest, biome, terrain, stone, desert, temp):
        self.__x = x
        self.__y = y
        self.__z = z
        self.__forest = evergreen_forest
        self.__birch = birch_forest
        self.__biome = biome
        self.__terrain = terrain
        self.__stone = stone
        self.__desert = desert
        self.__temp = temp

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def get_z(self):
        return self.__z

    def mod_z(self, new_z):
        self.__z = new_z

    def get_forest(self):
        return self.__forest

    def get_birch(self):
        return self.__birch

    def get_biome(self):
        return self.__biome

    def get_terrain(self):
        return self.__terrain

    def mod_terrain(self, new_terrain):
        self.__terrain = new_terrain

    def get_stone(self):
        return self.__stone

    def get_temp(self):
        return self.__temp

    def mod_temp(self, new_temp):
        self.__temp = new_temp

    def get_desert(self):
        return self.__terrain

    def mod_desert(self, new_desert):
        self.__terrain = new_desert


def draw(tiles, tile_ids):
    img = Image.new('RGB', (MAP_SIZE_X, MAP_SIZE_Y))
    print("Drawing...")

    for tile_id in tile_ids:
        x = tiles[tile_id].get_x()
        y = tiles[tile_id].get_y()
        z = tiles[tile_id].get_z()
        evergreen_forest = tiles[tile_id].get_forest()
        birch_forest = tiles[tile_id].get_birch()
        biome = tiles[tile_id].get_biome()
        terrain = tiles[tile_id].get_terrain()
        stone = tiles[tile_id].get_stone()
        temp = tiles[tile_id].get_temp()

        if x == MAP_SIZE_X or y == MAP_SIZE_Y:
            pass
        else:
            B = 0
            mine_type_roll = random.randrange(0, 1000)

            # HEIGHT

            if z < SEA_LEVEL:
                R = 0
                B = 1  # WATER
            elif SEA_LEVEL < z < ELEV_1:
                R = 40
            elif ELEV_1 < z < ELEV_2:
                R = 80
            elif ELEV_2 < z < ELEV_3:
                R = 120
            elif ELEV_3 < z < ELEV_4:
                R = 160
            else:
                R = 200

            if evergreen_forest > FOREST_SPAWN_VALUE and z > SEA_LEVEL:
                B = 61
                if temp < DESERT_TEMP - 125:
                    G = 201  # EVERGREEN TREE SNOW
                else:
                    G = 200
            elif birch_forest > FOREST_SPAWN_VALUE and z > SEA_LEVEL and (temp > DESERT_TEMP - 115):
                G = 202  # BIRCH TREE
                B = 61
            else:
                G = 0

            if biome > BIOME_SPAWN_VALUE and SEA_LEVEL < z < ELEV_1 - 0.02:  # FERTILE GRASS
                B = 81

            if (temp > DESERT_TEMP) and z > SEA_LEVEL:  # DESERT
                G = 0
                B = 41
                stone += 0.05
                mine_type_roll += 80
                roll = random.randint(0, 10)
                if SEA_LEVEL + 0.02 > z > SEA_LEVEL and roll > 6:  # PALM TREE
                    G = 203
                elif 7 < roll < 9:  # DECOR
                    G = random.randint(4, 6)

            if (temp < DESERT_TEMP - 125) and z > SEA_LEVEL:  # SNOW
                G = 0
                B = 101
                stone += 0.05
                mine_type_roll += 80
                roll = random.randint(0, 20)
                if roll == 20:
                    G = 209  # EXTRA GEYSIR SPAWNS FOR SNOW BIOME

            if temp < DESERT_TEMP:  # makes stone less common outside desert
                stone -= 0.05

            # HEX FEATURES

            roll = random.randrange(0, 100)
            if stone > STONE_SPAWN_VALUE:
                if z > SEA_LEVEL:
                    B = 21  # STONE HEX TYPE
                    G = 0  # REMOVE VEGETATION FROM STONE
                    if mine_type_roll > 990:  # DIAMOND
                        G = 204
                    elif 990 > mine_type_roll > 950:  # GOLD
                        G = 210
                    elif 950 > mine_type_roll > 805:  # MINERALS
                        G = 211
                    elif 805 > mine_type_roll > 500:  # MOUNTAIN
                        G = 207
                    elif 500 > mine_type_roll > 480:  # VOLCANO
                        G = 208

            elif 96 > roll > 80:  # FISH
                if z < SEA_LEVEL:
                    G = 205
            elif 80 > roll > 74:  # CATTLE
                if z > SEA_LEVEL and (birch_forest < FOREST_SPAWN_VALUE and evergreen_forest < FOREST_SPAWN_VALUE)\
                        and B == 61:
                    G = 206
            elif 74 > roll > 73:  # GEYSIR
                if z > SEA_LEVEL:
                    G = 209
                    if B == 0:  # this might fix something maybe
                        B = 61

            if G == 0 and z > SEA_LEVEL and B == 0:  # GRASS DECOR
                B = 61  # GRASS HEX
                roll = random.randint(0, 100)
                if roll < 20:
                    G = random.randint(1, 3)

            A = int(abs(terrain))

            img.mode = 'RGBA'
            img.putpixel((x, y), (R, G, B, A))

    img.save(FILE_LOCATION, 'png')
    print("Drawing successful!")


main()
