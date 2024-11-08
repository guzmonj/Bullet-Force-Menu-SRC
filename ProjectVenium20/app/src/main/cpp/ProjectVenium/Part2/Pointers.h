namespace Pointers {
    namespace Transform {
        void (*get_position_Injected)(void *, Vector3 *);
        void (*set_position_Injected)(void *, Vector3);
    }

    namespace Component /**UnityEngine**/ {
        void *(*get_transform)(void *);
    }

    namespace MonoBehaviour {
        void *(*get_photonView)(void *);
    }

    namespace HumanReferences {
        uint64_t head;
        uint64_t tHips;
        uint64_t tLeftThigh;
        uint64_t tLeftKnee;
        uint64_t tRightThigh;
        uint64_t tRightKnee;
        uint64_t tMiddleSpine;
        uint64_t tLeftArm;
        uint64_t tLeftForeArm;
        uint64_t tRightArm;
        uint64_t tRightForeArm;
    }

    namespace PlayerScript {
        uint64_t isMine;
        uint64_t humanMeshReferences;
        uint64_t mCamera;
        uint64_t isTeammateSkin;
        uint64_t crouching;
        uint64_t baseGunPosition;
        uint64_t spread;
        uint64_t minSpread;
        uint64_t visualSpread;
        uint64_t originalMinSpread;
        uint64_t hackprevention_doubleMPKills;
        uint64_t multiplayerNumberOfKills;

        void (*Jump)(void *);
        void (*Update)(void *);
        float (*get_health)(void *);
        void (*reloadWeapon)(void *);
        void (*toggleCrouch)(void *, bool);
        void (*addAmmo)(void *, int, int);
        void (*addAmmoToClip)(void *, int, int);
        void (*UpdateMPKills)(void *, int, int, bool);
    }

    namespace mainMenuButton {
        void *(*ExitToMainMenu)(void *);
    }

    namespace KillstreakManager {
        void (*AddKillToKillStreak)(void *);
    }

    namespace PopupMenuScript {
        void (*showPopup)(void *, monoString *, monoString *, int, int, float);
    }

    namespace PerksHandler {
        bool (*HasPerk)(void *, int);
    }

    namespace FlashScript {
        void (*Flash)(void *, float);
    }

    namespace OpenGL {
        void (*glDrawElements)(GLenum, GLsizei, GLenum, const void *);
        GLint (*glGetUniformLocation)(GLuint, const GLchar *);
    }

    namespace Camera {
        void (*set_nearClipPlane)(void *, float);
        Vector3 (*WorldToViewportPoint)(void *, Vector3, int) = (Vector3 (*)(void *, Vector3, int eye))nullptr;
    }
}