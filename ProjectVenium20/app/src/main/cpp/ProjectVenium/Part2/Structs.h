struct PlayerInfo {
    void *player, *photonView, *transform, *hipsTransform, *leftThighTransform, *leftKneeTransform,
        *rightThighTransform, *rightKneeTransform, *middleSpineTransform, *leftArmTransform,
        *leftForeArmTransform, *rightArmTransform, *rightForeArmTransform, *headTransform;

    Vector3 position, hipsPosition, leftThighPosition, leftKneePosition, rightThighPosition,
        rightKneePosition, middleSpinePosition, leftArmPosition, leftForeArmPosition, rightArmPosition,
        rightForeArmPosition, headPosition, screenPosition, leftKneeScreenPosition, headScreenPosition;
    bool isMine, isTeammate, crouching;
    float health;
};