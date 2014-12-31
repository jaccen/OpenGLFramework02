/* OpenGL関連のライブラリ */
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


/* SDL関連のライブラリ */
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_net.lib")


/* FBX関連のライブラリ */
#pragma comment(lib, "libfbxsdk-mt.lib")


/* Lua関連のライブラリ */
#pragma comment(lib, "lua5.1.lib")


/* Bullet関連のライブラリ */
#ifdef _DEBUG


#pragma comment(lib, "ConvexDecomposition_Debug.lib")
#pragma comment(lib, "BulletMultiThreaded_Debug.lib")
#pragma comment(lib, "BulletWorldImporter_Debug.lib")
#pragma comment(lib, "BulletSoftBody_Debug.lib")
#pragma comment(lib, "BulletDynamics_Debug.lib")
#pragma comment(lib, "BulletCollision_Debug.lib")
#pragma comment(lib, "BulletFileLoader_Debug.lib")
#pragma comment(lib, "LinearMath_Debug.lib")


#else


#pragma comment(lib, "ConvexDecomposition.lib")
#pragma comment(lib, "BulletMultiThreaded.lib")
#pragma comment(lib, "BulletWorldImporter.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletFileLoader.lib")
#pragma comment(lib, "LinearMath.lib")


#endif