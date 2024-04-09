#include "../../Precompiled.h"

void CAimBot::UpdateValues()
{
    this->m_flSmoothness = Config::Get<float>(g_Variables.m_flAimbotSmooth);
    this->m_flFOV = Config::Get<float>(g_Variables.m_flAimbotFOV);
}

void __fastcall CAimBot::CalcAngle(Vector& src, Vector& dst, QAngle& angles)
{
    Vector delta = dst - src;
    float hyp = delta.Length();
    angles.x = std::atan2(-delta.z, hyp) * (180.0f / M_PI);
    angles.y = std::atan2(delta.y, delta.x) * (180.0f / M_PI);
    angles.z = 0.0f;
}
    
void CAimBot::Run(CCSPlayerController* pEntity, C_CSPlayerPawn* pPawn)
{
    if (!Input::HandleInput(Config::Get<KeyBind_t>(g_Variables.m_AimBotKey)) || !Globals::m_pLocalPlayerController->m_bPawnIsAlive())
        return;

    this->UpdateValues();

    QAngle qAim;
    Vector src = Globals::m_pLocalPlayerPawn->GetEyePosition();
    Vector dst = pPawn->GetBonePosition(HEAD);

    CalcAngle(src, dst, qAim);

    if (qAim.Length() > m_flFOV) return;

    g_Memory.Write<QAngle>(Offsets::Client::dwViewAngles, qAim);
}