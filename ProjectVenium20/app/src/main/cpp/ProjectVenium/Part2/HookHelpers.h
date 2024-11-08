void getPos(void *transform, Vector3 position) { Pointers::Transform::get_position_Injected(transform, &position); }
Vector3 getPos(Vector3 position) { return ESP::WorldToScreen(camera, position, 2); }
void *getTra(uint64_t offset) { return *(void **)((uint64_t)oTransform + offset); }