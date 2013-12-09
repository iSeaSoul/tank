#ifndef __M_CONFIG__
#define __M_CONFIG__

#define FLOOR_HEIGHT 0.1f
#define FLOOR_WIDTH 300.0f
#define FLOOR_DEPTH 300.0f

#define PLATFORM_ROTATE_ANGLE_UNIT 2000
#define PLATFORM_HEIGHT 10.0f
#define PLATFORM_WIDTH 50.0f
#define PLATFORM_DEPTH 50.0f

#define TANK_HEIGHT 10.0f
#define TANK_WIDTH 10.0f
#define TANK_DEPTH 10.0f
#define TANK_STEP_UNIT 1.0f

#define BARREL_WIDTH 1.0f
#define BARREL_HEIGHT 1.0f
#define BARREL_DEPTH 10.0f

#define CAMERA_HEIGHT 120.0f
#define CAMERA_DEPTH -150.0f
#define CAMERA_WIDTH 30.0f

#define ENEMY_SIZE 5.0f
#define ENEMY_RANGE 100

#define BULLET_SPEED .05f
#define GAP_TIME 500

#define PLATFORM_ROTATE_MODE true
#define FIXED_VIEW false

#define TANK_TEXTURE "Texture\\tank.bmp"
#define FLOOR_TEXTURE "Texture\\floor.bmp"
#define ENEMY_TEXTURE "Texture\\enemy.bmp"

#define SafeRelease(pInterface) if(pInterface != NULL) {pInterface->Release(); pInterface=NULL;}
#define SafeDelete(pObject) if(pObject != NULL) {delete pObject; pObject=NULL;}

#endif
