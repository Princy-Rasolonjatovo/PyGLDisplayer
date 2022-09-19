from displayer import Displayer

import pickle


pathTestData = "E://Documents//Dev//3DScanner//Data//"
with open(pathTestData + "susane_for_gl_display.bin", "rb") as fp:
    vertices= pickle.load(fp)
    _unpacked = []
    for vec3 in vertices:
        _unpacked.extend(vec3)
    susane_vertices = _unpacked
with open(pathTestData + "male_head_binary.bin", "rb") as fp:
    male_head_vertices = pickle.load(fp)
with open(pathTestData + "grid_14_14.bin", "rb") as fp:
    grid = pickle.load(fp)

if __name__ == "__main__":
    # Test
    # Display a window with width : 600 and height: 400
    # antialias : x4
    disp = Displayer(800, 600, 4)
    #disp.display()
    vbo = [-1.0, -1.0, 0.0,
            1.0, -1.0, 0.0,
            0.0,  1.0, 0.0]


    disp.setvbo(susane_vertices)
    #disp.setvbo(male_head_vertices)
    # disp.setgrid(grid)
    # disp.setvbo(vertices[:3*3])

    # disp.setshaderspaths(vertexShaderPath="A:\\Documents\\Dev\\TroisDevo\\Displayer\\res\\shaderTests\\SimpleTransform.vertexshader", 
    # fragmentShaderPath="A:\\Documents\\Dev\\TroisDevo\\Displayer\\res\\shaderTests\\SingleColor.fragmentshader")
    disp.setshaderspaths(
        vertexShaderPath="../../res/shaderTests/SimpleTransform.vertexshader", 
        fragmentShaderPath="../../res/shaderTests/SingleColor.fragmentshader")
    disp.display()
