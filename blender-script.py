import bpy
import math

obj = bpy.context.active_object.data
vertices = obj.vertices

size = len(vertices);
out = "// " + str(size) + "\n#include \"./headers/voxelmodels.h\"\n\n"
out += "Voxel monkey[MESH_SIZE] __attribute__((aligned(8))) =\n"
out += "{\n";

i = 0
idx = set()
for poly in obj.polygons:
    for id in poly.loop_indices:
        loop = obj.loops[id]
        v = loop.vertex_index
        
        if v not in idx:
            idx.add(v)
            x = math.floor(vertices[v].co.x)
            y = math.floor(vertices[v].co.y)
            z = math.floor(vertices[v].co.z)
            
            c = obj.vertex_colors.active.data[i].color
            
            r = math.floor(c.r*255)
            g = math.floor(c.g*255)
            b = math.floor(c.b*255)
        
            color = str(hex((r << 24) + (g << 16) + (b << 8) + 255))

            out += "\t{{" + str(x) + "," + str(y) + "," + str(z) + "}," + color + "},\n";
        
        i += 1
        

out = out[:-2] + "\n};\n";

filename = "./voxelmodels.cpp";
f = open(filename, "w");
f.write(out);

filename = "./headers/voxelmodels.h";
f = open(filename, "w");
out = "/*\n"
out += "* Cloud of voxels (COV) project\n"
out += "* Author: mcidclan, m [.D'O'T.] cid [.D'O'T.] clan [.A'T.] gmail [.D'O'T.] com\n"
out += "* Date: 2020\n"
out += "*/\n\n"
out += "#ifndef VOXELMODELS_H\n"
out += "#define VOXELMODELS_H\n\n"
out += "\t#include \"types.h\"\n\n"
out += "\tconst UI MESH_SIZE  = "+str(size)+";\n\n"
out += "#endif\n"
f.write(out);

print("Please make sure that MESH_SIZE is well set with the following value: " + str(size), "\n");
