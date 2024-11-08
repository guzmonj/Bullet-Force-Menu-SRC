#pragma once
#include "HookHelpers.h"

namespace Hooks {
    namespace mainMenuButton {
        void ExitToMainMenu(void *_this) {
            Pointers::mainMenuButton::ExitToMainMenu(_this);
            camera = nullptr;
            oTransform = nullptr;
            for (auto & pi : playerInfo) pi = new PlayerInfo();
        }
    }

    namespace FlashScript {
        void Flash(void *_this, float time) {
            if (!menus[2].mods[2].is) Pointers::FlashScript::Flash(_this, time);
        }
    }

    namespace PerksHandler {
        bool HasPerk(void *_this, int perk){
            return menus[0].mods[4].is || Pointers::PerksHandler::HasPerk(_this, perk);
        }
    }

    namespace KillstreakManager {
        void AddKillToKillStreak(void *_this) {
            if (!menus[4].mods[0].is || (menus[4].mods[0].is && menus[3].mods[0].is)) {
                menus[3].mods[0].is = false;
                Pointers::KillstreakManager::AddKillToKillStreak(_this);
            }
        }
    }

    namespace PopupMenuScript {
        void showPopup(void *_this, monoString *text, monoString *nameText, int points, int weaponType, float size) {
            if (!menus[3].mods[0].is && !menus[4].mods[0].is)
                Pointers::PopupMenuScript::showPopup(_this, text, nameText, points, weaponType, size);
        }
    }

    namespace PlayerScript {
        void Jump(void *_this) {
            if (menus[0].mods[0].is && *(bool **)((uint64_t)_this + Pointers::PlayerScript::isMine)) {
                void *transform = Pointers::Component::get_transform(_this);
                Vector3 position;
                if (transform) {
                    Pointers::Transform::get_position_Injected(transform, &position);
                    position.Y = position.Y + 5;
                    Pointers::Transform::set_position_Injected(transform, position);
                }
            } else Pointers::PlayerScript::Jump(_this);
        }

        void UpdateMPKills(void *_this, int value, int playerKilledId, bool updateGunGameScore = true) {
            if (blockKills && !menus[3].mods[0].is) blockKills = false;
            else Pointers::PlayerScript::UpdateMPKills(_this, value, playerKilledId, updateGunGameScore);
            if (menus[3].mods[0].is) {
                Pointers::PlayerScript::UpdateMPKills(_this, value - 1, playerKilledId, updateGunGameScore);
                *(int *)((uint64_t)_this + Pointers::PlayerScript::multiplayerNumberOfKills) = value;
                *(int *)((uint64_t)_this + Pointers::PlayerScript::hackprevention_doubleMPKills) = value << 1;
            }
        }

        void reloadWeapon(void *_this) {
            if (menus[1].mods[0].is) {
                for (int i = 0; i < 80; i++) {
                    Pointers::PlayerScript::addAmmoToClip(_this, 1, i);
                    Pointers::PlayerScript::addAmmo(_this, 1, i);
                }
            } else Pointers::PlayerScript::reloadWeapon(_this);
        }

        void Update(void *_this) {
            Pointers::PlayerScript::Update(_this);
            if (esp_timer >= 10) {
                esp_timer = 0;
                for (auto & pi : playerInfo) pi = new PlayerInfo();
                return;
            }  for (int i = 0; i < 100; i++) {
                PlayerInfo *pi = playerInfo[i];
                if (!pi->player) pi->player = _this;
                if (pi->player == _this) {
                    pi->transform = Pointers::Component::get_transform(_this);
                    void *oTransform = *(void **)((uint64_t)pi->player + Pointers::PlayerScript::humanMeshReferences);
                    if (oTransform) {
                        pi->headTransform = getTra(Pointers::HumanReferences::head);
                        pi->hipsTransform = getTra(Pointers::HumanReferences::tHips);
                        pi->leftThighTransform = getTra(Pointers::HumanReferences::tLeftThigh);
                        pi->leftKneeTransform = getTra(Pointers::HumanReferences::tLeftKnee);
                        pi->rightThighTransform = getTra(Pointers::HumanReferences::tRightThigh);
                        pi->rightKneeTransform = getTra(Pointers::HumanReferences::tRightKnee);
                        pi->middleSpineTransform = getTra(Pointers::HumanReferences::tMiddleSpine);
                        pi->leftArmTransform = getTra(Pointers::HumanReferences::tLeftArm);
                        pi->leftForeArmTransform = getTra(Pointers::HumanReferences::tLeftForeArm);
                        pi->rightArmTransform = getTra(Pointers::HumanReferences::tRightArm);
                        pi->rightForeArmTransform = getTra(Pointers::HumanReferences::tRightForeArm);
                    } if (pi->transform && pi->headTransform) {
                        getPos(pi->transform, pi->position);
                        getPos(pi->hipsTransform, pi->hipsPosition);
                        getPos(pi->leftThighTransform, pi->leftThighPosition);
                        getPos(pi->leftKneeTransform, pi->leftKneePosition);
                        getPos(pi->rightThighTransform, pi->rightThighPosition);
                        getPos(pi->rightKneeTransform, pi->rightKneePosition);
                        getPos(pi->middleSpineTransform, pi->middleSpinePosition);
                        getPos(pi->leftArmTransform, pi->leftArmPosition);
                        getPos(pi->leftForeArmTransform, pi->leftForeArmPosition);
                        getPos(pi->rightArmTransform, pi->rightArmPosition);
                        getPos(pi->rightForeArmTransform, pi->rightForeArmPosition);
                        getPos(pi->headTransform, pi->headPosition);
                    } pi->photonView = Pointers::MonoBehaviour::get_photonView(_this);
                    if (pi->photonView) {
                        if (pi->transform) {
                            Pointers::Transform::get_position_Injected(pi->transform, &pi->position);
                            pi->health = Pointers::PlayerScript::get_health(pi->player);
                            pi->isTeammate = *(bool*)((uint64_t)_this + Pointers::PlayerScript::isTeammateSkin);
                            pi->isMine = *(bool *)((uint64_t)_this + Pointers::PlayerScript::isMine);
                            pi->crouching = *(bool *)((uint64_t)_this + Pointers::PlayerScript::crouching);
                            if (pi->crouching && menus[0].mods[1].is && pi->isMine && crouch_timer >= 300) {
                                crouch_timer = 0;
                                pi->position.Y = pi->position.Y - 2;
                                Pointers::Transform::set_position_Injected(pi->transform, pi->position);
                                *(bool *)((uint64_t)_this + Pointers::PlayerScript::crouching) = false;
                                Pointers::PlayerScript::toggleCrouch(_this, true);
                            } if (pi->isMine && pi->health >= 5) {
                                esp_timer += 1;
                                crouch_timer += 1;
                                camera = *(void **)((uint64_t)_this + Pointers::PlayerScript::mCamera);
                                if (camera) {
                                    if (menus[2].mods[4].is) Pointers::Camera::set_nearClipPlane(camera, .777f);
                                    else Pointers::Camera::set_nearClipPlane(camera, 0.1f);
                                } timescale_timer += 1;
                                if (menus[0].mods[3].is && timescale_timer >= 4) {
                                    timescale_timer = 0;
                                    Pointers::PlayerScript::Update(_this);
                                } if (menus[1].mods[1].is) {
                                    *(float *)((uint64_t)pi->player + Pointers::PlayerScript::minSpread) = 0.1f;
                                    *(float *)((uint64_t)pi->player + Pointers::PlayerScript::spread) = 0.1f;
                                    *(float *)((uint64_t)pi->player + Pointers::PlayerScript::visualSpread) = 0.1f;
                                    *(float *)((uint64_t)pi->player + Pointers::PlayerScript::originalMinSpread) = 0.1f;
                                } if (menus[1].mods[3].is) {
                                    Vector3 position = *(Vector3 *)((uint64_t)pi->player + Pointers::PlayerScript::baseGunPosition); //-0.228006, 0.024005, 0.000000 for M4A1
                                    position.Z = 3.337f;
                                    *(Vector3 *)((uint64_t)pi->player + Pointers::PlayerScript::baseGunPosition) = position;
                                }
                            } if (camera) {
                                pi->screenPosition = getPos(pi->position);
                                pi->leftKneeScreenPosition = getPos(pi->leftKneePosition);
                                pi->headScreenPosition = getPos(pi->rightForeArmPosition);
                            }
                        }
                    } break;
                }
            }
        }
    }

    namespace OpenGL {
        bool SameShader(const char *shader) {
            GLint currProgram;
            glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
            return Pointers::OpenGL::glGetUniformLocation(currProgram, shader) != -1;
        }

        void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
            Pointers::OpenGL::glDrawElements(mode, count, type, indices);
            if (mode != GL_TRIANGLES || count < 1000) return;
            if (SameShader("_CamoPatternMap_ST") || SameShader("_CamoBlackTint") || SameShader("_CamoRedTint") || SameShader("_CamoGreenTint") || SameShader("_CamoBlueTint") || SameShader("_CamoPatternMap")){
                if (menus[2].mods[0].is) {
                    glDisable(GL_DEPTH_TEST);
                    Pointers::OpenGL::glDrawElements(mode, count, type, indices);
                    glEnable(GL_DEPTH_TEST);
                } if (menus[2].mods[1].is) {
                    glDepthRangef(1, 0.5);
                    glColorMask(1, 1, 1, 0);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
                    //glBlendFunc(GL_CONSTANT_COLOR, GL_ZERO);
                    glBlendColor(1, 0, 0, 1);
                    Pointers::OpenGL::glDrawElements(GL_LINES, count, type, indices);
                    glDepthRangef(0.5, 1);
                    glDisable(GL_BLEND);
                }
            }
        }
    }
}