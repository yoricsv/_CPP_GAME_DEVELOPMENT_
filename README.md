# _CPP_GAME_DEVELOPMENT_

# LEARN C++ (GAME DEVELOPMENT)

> ***NOTE***: "C++ GAME DEVELOPMENT PROFESSIONAL" *(Start 10-nov-2021)*
> ***NOTE***: I don't mark topics without a description (READMEs).

### COURSE CONTENT

- [ ] **001 MICRO ENGINE**:
  - [X] _1 IDE setting up
  - [X] **RESULT:** Application [*001.2_CppHelloWorld_std17*][CppGameDev_1]
  - [X] **RESULT:** Application [*001.2_CppHelloWorld_std17-O1*][CppGameDev_2]
  - [X] **RESULT:** Application [*001.2_CppHelloWorld_std17-O2*][CppGameDev_3]
  - [ ] **RESULT:** Application [*001.2_CppHWRandNumber_std17-O2*][CppGameDev_4]
  - [ ] **RESULT:** Application [*001.3_CppHWScanfAnalogue*][CppGameDev_5]
  - [X] _2 [CMake][CMake]
    - [X] **Step 1**: [A Basic Starting Point Build and Run][stp1]
      - [X] *Adding a Version Number and Configured Header File*
      - [X] *Specify the C++ Standard*
      - [X] *Rebuild*
    - [X] **Step 2**: [Adding a Library][stp2]
    - [X] **Step 3**: [Adding Usage Requirements for a Library][stp3]
    - [X] **Step 4**: [Installing and Testing][stp4]
      - [X] *Install Rules*
      - [X] *Testing Support*
    - [X] **Step 5**: [Adding System Introspection][stp5]
    - [X] **Step 6**: [Adding a Custom Command and Generated File][stp6]
    - [X] **Step 7**: [Packaging an Installer][stp7]
    - [X] **Step 8**: [Adding Support for a Testing Dashboard][stp8]
    - [X] **Step 9**: [Selecting Static or Shared Libraries][stp9]
    - [X] **Step 10**: [Adding Generator Expressions][stp10]
    - [X] **Step 11**: [Adding Export Configuration][stp11]
    - [X] **Step 12**: [Packaging Debug and Release][stp12]
  - [X] _3 Main game loop
  - [ ] **RESULT:** Application [*000_CppClassGame*][CppGameDev_6]
  - [X] **RESULT:** Application [*003.1_CppOpenGL*][CppGameDev_7]
  - [ ] _4 Input: keyboard, mouse, gamepad, joystick, device emulation
  - [ ] _5 OpenGL: (*ES2.0: Initialization, extensions, getting function pointers*)
    - [X] [**How OpenGL works**: (*Software rendering*)][5_OpenGL]
    - [ ] **OpenGL Step 1**: [Bresenham’s Line Drawing Algorithm][OGLstp1]
    - [ ] **OpenGL Step 2**: [Triangle rasterization and back face culling][OGLstp2]
    - [ ] **OpenGL Step 3**: [Hidden faces removal (z-buffer)][OGLstp3]
    - [ ] **OpenGL Step 4**: [Perspective projection][OGLstp4]
    - [ ] **OpenGL Step 5**: [Moving the camera][OGLstp5]
    - [ ] **OpenGL Step 6**: [Shaders for the software renderer][OGLstp6]
    - [ ] **OpenGL Step 7**: [Tangent space normal mapping][OGLstp7]
    - [ ] **OpenGL Step 8**: [Shadow mapping][OGLstp8]
    - [ ] **OpenGL Step 9**: [Ambient occlusion][OGLstp9]
    - [ ] **OpenGL Step 10**: [Real OpenGL (GLSL) application][OGLstp10]
    - [ ] **OpenGL Step 11**: [Technical difficulties: Vectors and Matrices classes][OGLstp11]
    - [ ] **OpenGL Step 12**: [Technical difficulties: linear interpolation with perspective deformations][OGLstp12]
    - [ ] **OpenGL Step 13**: [Visual troubleshooting][OGLstp13]
  - [ ] _6 Primitive rasteurization, vertex shader, fragment shader
  - [ ] _7 Texturing: buffers, textures, surfaces, attributes and constants (uniforms)
  - [ ] _8 Matrices and vectors, display of the movement, scaling and rotation matrices
  - [ ] _9 Vertex texture animation, morphing
  - [ ] _10 Sound output principle, the mixer
  - [ ] _11 Audio formats, codecs, containers and effects
- [ ] **002 GAME PROTOTYPE**
  - [ ] _1 Full-scale prototyping
  - [ ] _2 Writing UML, class diagrams
  - [ ] _3 Development of the main algorithm
  - [ ] _4 Collision detection
  - [ ] _5 Development of data formats (scene, levels, objects, etc.)
  - [ ] _6 Loading and reloading the game (levels). Debugging, tricks to make development easier
- [ ] **003 GAME EDITOR**
  - [ ] _1 Adding ImGui
  - [ ] _2 Level editor
  - [ ] _3 Object editor
  - [ ] _4 Screen editor
  - [ ] _5 Creation of multiple levels and a finished game
  - [ ] _6 Loading and reloading the game (levels). Debugging, tricks to make development easier
- [ ] **004 Porting the game to Android OS**
  - [ ] _1 Installing and configuring Android Strudio
  - [ ] _2 Changing file uploads
  - [ ] _3 Parse the AndroidManifest.xml
  - [ ] _4 Adding a new type of control (touch) to the game

<!--
* [*001.2_CppHelloWorld_std17*][CppGameDev_1]
* [*001.2_CppHelloWorld_std17-O1*][CppGameDev_2]
* [*001.2_CppHelloWorld_std17-O2*][CppGameDev_3]
* [*001.2_CppHWRandNumber_std17-O2*][CppGameDev_4]
* [*001_3_CppHWScanfAnalogue*][CppGameDev_5]
* [*000_CppClassGame*][CppGameDev_6]
* [*003.1_CppOpenGL*][CppGameDev_7]
-->

[CppGameDev_1]: https://github.com/yoricsv/001_2_CppHelloWorld_std17.git
[CppGameDev_2]: https://github.com/yoricsv/001_2_CppHelloWorld_std17-O1.git
[CppGameDev_3]: https://github.com/yoricsv/001_2_CppHelloWorld_std17-O2.git
[CppGameDev_4]: https://github.com/yoricsv/001_2_CppHWRandNumber_std17-O2.git
[CppGameDev_5]: https://github.com/yoricsv/001_3_CppScanfAnalogue.git
[CppGameDev_6]: https://github.com/yoricsv/000_CppClassGame.git
[CppGameDev_7]: 003_1_CppOpenGL
[CMake]:        002_CppCMake/README.md
[stp1]:         002_CppCMake/002_1_BasicStartingPoint
[stp2]:         002_CppCMake/002_2_AddingLibrary
[stp3]:         002_CppCMake/002_3_UsageReqForLib
[stp4]:         002_CppCMake/002_4_InstallAndTest
[stp5]:         002_CppCMake/002_5_SysIntrospection
[stp6]:         002_CppCMake/002_6_ComFileGen
[stp7]:         002_CppCMake/002_7_BuildInstall
[stp8]:         002_CppCMake/002_8_Dashboard
[stp9]:         002_CppCMake/002_9_StaticShared
[stp10]:        002_CppCMake/002_10_GenExpression
[stp11]:        002_CppCMake/002_11_ExportConfig
[stp12]:        002_CppCMake/002_12_PackDebRel
[5_OpenGL]:     005_CppOwnOpenGLAnalogue_/README.md
[OGLstp1]:      005_CppOwnOpenGLAnalogue_/005_1_BresenhamAlgorithm
[OGLstp2]:      005_CppOwnOpenGLAnalogue_/005_2_TrialgleRasterization
[OGLstp3]:      005_CppOwnOpenGLAnalogue_/005_3_Z-buffer
[OGLstp4]:      005_CppOwnOpenGLAnalogue_/005_4_PerspectiveProjection
[OGLstp5]:      005_CppOwnOpenGLAnalogue_/005_5_MovingCamera
[OGLstp6]:      005_CppOwnOpenGLAnalogue_/005_6_SoftwareShadersRendering
[OGLstp7]:      005_CppOwnOpenGLAnalogue_/005_7_TangentSpaceMapping
[OGLstp8]:      005_CppOwnOpenGLAnalogue_/005_8_ShadowMapping
[OGLstp9]:      005_CppOwnOpenGLAnalogue_/005_9_AmbientOcclusion
[OGLstp10]:     005_CppOwnOpenGLAnalogue_/005_10_OpenGL(GLSL)Application
[OGLstp11]:     005_CppOwnOpenGLAnalogue_/005_11_VectorsAndMatricesClasses
[OGLstp12]:     005_CppOwnOpenGLAnalogue_/005_12_LinearInterpolation
[OGLstp13]:     005_CppOwnOpenGLAnalogue_/005_13_VisualTroubleshooting
