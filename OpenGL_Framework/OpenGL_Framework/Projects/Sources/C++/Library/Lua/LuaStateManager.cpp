/* �w�b�_�t�@�C�� */
#include "LuaStateManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief Lua
//! @brief Lua�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Lua
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LuaStateManager::C_LuaStateManager() :

        // �������
        upImpl_(std::make_unique<C_LuaManagerStateImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LuaStateManager::~C_LuaStateManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g���쐬����
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::Create(const std::string& rId)
    {
        upImpl_->Create(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g��j������
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::Destroy(const std::string& rId)
    {
        upImpl_->Destroy(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g��S�Ĕj������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �X�^�b�N�̓��e���o�͂���
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::PrintStack(const std::string& rId)
    {
        upImpl_->PrintStack(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return Lua�X�e�[�g
     *
     ****************************************************************/
    boost::optional<const LuaStatePtr&> C_LuaStateManager::GetState(const std::string& rId) const
    {
        return upImpl_->GetState(rId);
    }
}