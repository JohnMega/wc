
//#define DEBUG

#define NOTHING_KEY 0
#define ESC_KEY 27
#define MENU_SCROLL_KEY 's'
#define ENTER_KEY '\r'
#define ARROW_LEFT_KEY 0x4B
#define ARROW_RIGHT_KEY 0x4D
#define ARROW_UP_KEY 0x48
#define ARROW_DOWN_KEY 0x50
#define DELETE_KEY 'f'
#define FREEZE_KEY 'p'
#define PARAB_SPAWN_KEY 'g'
#define COLOR_CHANGE_KEY 'v'
#define RAY_FROM_CAMERA_KEY 'h'
#define ENABLE_MOVEMENT_ARROWS 'q'
#define ENABLE_ROTATED_CIRCLES 'e'
#define ENABLE_MOVEMENT_SCALES 'r'

// Light power inc/dec keys
#define INC_LIGHT_POWER_KEY 'i'
#define DEC_LIGHT_POWER_KEY 'o'

// Size inc/dec keys
#define BASE_LENGTH_INC_KEY 'q'
#define BASE_LENGTH_DEC_KEY '1'
#define ADDITIONAL_LENGTH_INC_KEY 't'
#define ADDITIONAL_LENGTH_DEC_KEY '4'

#define BASE_WIDTH_INC_KEY 'e'
#define BASE_WIDTH_DEC_KEY '2'
#define ADDITIONAL_WIDTH_INC_KEY 'y'
#define ADDITIONAL_WIDTH_DEC_KEY '5'

#define HEIGHT_INC_KEY 'r'
#define HEIGHT_DEC_KEY '3'

// Rotation keys
#define X_AXIS_ROTATION_KEY 'z'
#define Y_AXIS_ROTATION_KEY 'x'
#define Z_AXIS_ROTATION_KEY 'c'


#define UPROPERTY_(TypeName, VarName)\
bool isActorHas##TypeName() const noexcept override\
{\
	return true;\
}\
TypeName* Get##TypeName() noexcept override\
{\
	return VarName;\
}\
private:\

#define UPROPERTY(TypeName, VarName) UPROPERTY_(TypeName, VarName)

#define DEFINE_CUBEMAP() \
StaticMesh* currentCubemap;\
bool isActorHasCubemap() const noexcept override\
{\
	return currentCubemap;\
}\
StaticMesh* GetCubemap() noexcept override\
{\
    return currentCubemap;\
}\
void AttachCubemap(StaticMesh* cubemap) override\
{\
	currentCubemap = cubemap;\
}\
void DetachCubemap() noexcept\
{\
    currentCubemap = nullptr;\
}\
void CubemapActiveCheck()\
{\
    bool isCubemapActive = false;\
    for (size_t i = 1; i < actors.size(); ++i)\
    {\
        if (!actors[i]->isActorHasStaticMesh()) continue;\
        \
        if (currentCubemap == actors[i]->GetStaticMesh())\
        {\
            isCubemapActive = true;\
            break;\
        }\
    }\
    \
    if (!isCubemapActive) DetachCubemap();\
}\

#define DEFINE_TRIGGER() \
std::vector<std::pair<StaticMesh*, int>> currentTriggers;\
bool isActorHasTrigger() const noexcept override\
{\
	return true;\
}\
std::vector<std::pair<StaticMesh*, int>> GetTrigger() noexcept override\
{\
    return currentTriggers;\
}\
void AttachTrigger(StaticMesh* trigger, int typeOfTrigger) override\
{\
	currentTriggers.push_back({trigger, typeOfTrigger});\
}\
void DetachTrigger(StaticMesh* trigger) override\
{\
    for(size_t i = 0; i < currentTriggers.size(); ++i)\
        if(currentTriggers[i].first == trigger) currentTriggers[i].first = nullptr; \
}\

#define IS_ACTOR_HAS_TYPE_(ActorName, TypeName)\
if(ActorName->isActorHas##TypeName())\

#define IS_ACTOR_HAS_TYPE(ActorName,TypeName) IS_ACTOR_HAS_TYPE_(ActorName, TypeName)

#define IS_ACTOR_HAS_NOT_TYPE_(ActorName, TypeName)\
if(!ActorName->isActorHas##TypeName())\

#define IS_ACTOR_HAS_NOT_TYPE(ActorName,TypeName) IS_ACTOR_HAS_NOT_TYPE_(ActorName, TypeName)