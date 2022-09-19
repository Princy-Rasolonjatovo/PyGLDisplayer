from distutils.core import Extension, setup

def main() : 
    setup(
        name = "displayer",
        version = "0.0.1",
        description = "Displayer using opengl",
        author = "Max",
        author_email = "ericrasolonjatovo@yahoo.fr",
        ext_modules=[
            Extension(
                "displayer",
                sources=[
                     # tony oa soloy code mampesa Path_iterdir
                    "src/displayer.cpp",
                    "src/shader.cpp",
                    "src/displayer_native.cpp",
                    "src/gizmo_system.cpp",
                    "src/handlers_keyboard_mouse.cpp",
                    "src/viewport.cpp"
                ],
                include_dirs=[
                    "./includes/",
                    "C:/softwares/glew-1.13.0/include/",
                    "C:/softwares/glfw-3.1.2/include/",
                    "C:/softwares/glm-0.9.7.1/"
                ],
                libraries=[
                     # tony oa soloy code mampesa *Path_iterdir.filter(isfile_endsWith(".lib")).map(lambda x: )
                    "opengl32", # Dafuck aiz no misy anito ?(default anaty sys ngamba)
                    "glu32", # Dafuck aiz no misy anito ?
                    "glew32d",
                    "glew32sd",
                    "glfw3dll",
                    "glfw3",
                    "GLEW_1130",
                    "kernel32",
                    "user32",
                    "gdi32",
                    "winspool",
                    "shell32",
                    "ole32",
                    "oleaut32",
                    "uuid",
                    "comdlg32",
                    "advapi32"
                    
                ],
                library_dirs=[
                    "./staticLibs/", 
                ],
                # runtime_library_dirs=[
                #     "./dynamicLibs/"
                # ]
            )
        ]
    )
if __name__ == "__main__":
    main()