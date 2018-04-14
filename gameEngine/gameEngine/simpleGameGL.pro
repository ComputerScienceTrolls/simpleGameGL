TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./OPENGL/headers/ ./OPENAL/headers/ ./SOIL2/headers/

SOURCES += main.cpp AbstractScene.cpp AbstractSprite.cpp Camera.cpp DrawSceneObject.cpp KeyHandler.cpp MovingSceneObject.cpp ResourceManager.cpp SceneDirector.cpp Scene.cpp SceneObject.cpp Shader.cpp Sound.cpp Sprite.cpp sprite_renderer.cpp Texture.cpp ./SensorActuators/AbstractActuator.cpp ./SensorActuators/AbstractSensor.cpp ./SensorActuators/ActiveActuator.cpp ./SensorActuators/AlwaysSensor.cpp ./SensorActuators/CameraActuator.cpp ./SensorActuators/CheckBoundsSensor.cpp ./SensorActuators/KeyboardSensor.cpp ./SensorActuators/MotionActuator.cpp ./SensorActuators/ParentActuator.cpp ./SensorActuators/PositionActuator.cpp ./SensorActuators/SceneActuator.cpp ./SensorActuators/SoundActuator.cpp ./SensorActuators/TimesActuator.cpp ./SensorActuators/VisibilityActuator.cpp ./SensorActuators/CollisionSensor.cpp ./Colliders/AbstractCollider.cpp ./Colliders/BoxCollider.cpp ./Colliders/CircleCollider.cpp ./Colliders/Edge.cpp ./Colliders/PolyCollider.cpp


HEADERS += AbstractScene.h AbstractSprite.h Camera.h DrawSceneObject.h KeyHandler.h MovingSceneObject.h ResourceManager.h SceneDirector.h Scene.h SceneObject.h Shader.h Sound.h Sprite.h sprite_renderer.h Texture.h ./SensorActuators/AbstractActuator.h ./SensorActuators/AbstractSensor.h ./SensorActuators/ActiveActuator.h ./SensorActuators/AlwaysSensor.h ./SensorActuators/CameraActuator.h ./SensorActuators/CheckBoundsSensor.h ./SensorActuators/KeyboardSensor.h ./SensorActuators/MotionActuator.h ./SensorActuators/ParentActuator.h ./SensorActuators/PositionActuator.h ./SensorActuators/SceneActuator.h ./SensorActuators/SoundActuator.h ./SensorActuators/TimesActuator.h ./SensorActuators/VisibilityActuator.h ./SensorActuators/CollisionSensor.h ./Colliders/AbstractCollider.h ./Colliders/BoxCollider.h ./Colliders/CircleCollider.h ./Colliders/Edge.h ./Colliders/PolyCollider.h

unix|win32: LIBS += -lglfw

unix|win32: LIBS += -lGLEW

unix|win32: LIBS += -lGLU

unix|win32: LIBS += -lglut

unix|win32: LIBS += -lGL

unix|win32: LIBS += -lopenal

#unix|win32: LIBS += -lAL

unix|win32: LIBS += -lalut

unix|win32: LIBS += ./SOIL2/headers/libsoil2-debug.a
