/* ヘッダファイル */
#include "OptionSmallBeamCollisionEffect.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Random/RandomGenerator.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include <sstream>


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_OptionSmallBeamCollisionEffect::C_OptionSmallBeamCollisionEffect(const std::string& rId, int32_t type) : C_BaseEffect(rId, type)
    {
        assert(Lua::C_LuaStateManager::s_GetInstance()->GetState());
        pLuaState_ = Lua::C_LuaStateManager::s_GetInstance()->GetState().get();

        assert(Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pCIRCLE_01));
        wpCircleParticleSystem_ = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pCIRCLE_01).get();

        assert(Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pRING_01));
        wpRingParticleSystem_ = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pRING_01).get();;
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OptionSmallBeamCollisionEffect::~C_OptionSmallBeamCollisionEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OptionSmallBeamCollisionEffect::DoUpdate()
    {
        if (wpCircleParticleSystem_.expired() == false && wpRingParticleSystem_.expired() == false)
        {
            auto pCircleParticleSystem = wpCircleParticleSystem_.lock();
            auto pRingParticleSystem = wpRingParticleSystem_.lock();

#ifdef _DEBUG

            try
            {
                // エフェクトのロジックを処理
                existenceFlag_ = luabind::call_function<bool>(pLuaState_.get(),
                                                              "OptionSmallBeamCollisionEffectLogic",
                                                              boost::ref(*pCircleParticleSystem.get()),
                                                              boost::ref(*pRingParticleSystem.get()),
                                                              boost::ref(frameCounter_),
                                                              boost::ref(*Random::C_RandomGenerator::s_GetInstance()),
                                                              boost::ref(position_)) ? true : false;
            }
            catch (luabind::error &rErrorInfo)
            {
                luabind::object errorMessage(luabind::from_stack(rErrorInfo.state(), -1));

                std::stringstream stream;
                stream << errorMessage << std::endl;

                PrintLog("[ C_OptionSmallBeamCollisionEffect::DoUpdate ] : 関数の呼び出しに失敗しました。\n");
                PrintLog("                エラーメッセージ : %s\n", stream.str().c_str());

                existenceFlag_ = false;
            }

#else

            // エフェクトのロジックを処理
            existenceFlag_ = luabind::call_function<bool>(pLuaState_.get(),
                                                          "OptionSmallBeamCollisionEffectLogic",
                                                          boost::ref(*pCircleParticleSystem.get()),
                                                          boost::ref(*pRingParticleSystem.get()),
                                                          boost::ref(frameCounter_),
                                                          boost::ref(*Random::C_RandomGenerator::s_GetInstance()),
                                                          boost::ref(position_)) ? true : false;

#endif

        }
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OptionSmallBeamCollisionEffect::DoDraw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OptionSmallBeamCollisionEffect::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}