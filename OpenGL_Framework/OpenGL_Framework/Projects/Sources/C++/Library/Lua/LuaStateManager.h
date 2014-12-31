/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Assert/AssertSingleton.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>


//-------------------------------------------------------------
//!
//! @brief Lua
//! @brief Lua�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Lua
{
    /* �ʖ� */
    using LuaStatePtr = std::shared_ptr<lua_State>;                                                     // LuaStatePtr�^


    namespace
    {
        /* ID */
        namespace ID
        {
            const char* s_pGLOBAL = "Global";                                                           ///< @brief �S�̂Ŏg�p�\
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief Lua�X�e�[�g�}�l�[�W���[
    //! @brief Lua�X�e�[�g���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_LuaStateManager : public Singleton::C_AssertSingleton<C_LuaStateManager>
    {
    public:
        C_LuaStateManager();                                                                                // �R���X�g���N�^
        ~C_LuaStateManager() override;                                                                      // �f�X�g���N�^
        void Create(const std::string& rId);                                                                // Lua�X�e�[�g���쐬
        void Destroy(const std::string& rId);                                                               // Lua�X�e�[�g��j��
        void AllDestroy();                                                                                  // Lua�X�e�[�g��S�Ĕj��
        void PrintStack(const std::string& rId = ID::s_pGLOBAL);                                            // �X�^�b�N�̓��e���o��
        boost::optional<const LuaStatePtr&> GetState(const std::string& rId = ID::s_pGLOBAL) const;         // Lua�X�e�[�g���擾
    private:
        /* �O���錾 */
        class C_LuaManagerStateImpl;

        std::unique_ptr<C_LuaManagerStateImpl> upImpl_;                                                     /// < brief �������
    };
}
