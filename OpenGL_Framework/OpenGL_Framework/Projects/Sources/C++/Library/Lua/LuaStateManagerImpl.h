/* �w�b�_�t�@�C�� */
#include "LuaStateManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief Lua
//! @brief Lua�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Lua
{
    //-------------------------------------------------------------
    //!
    //! @brief Lua�}�l�[�W���[�C���v�������g
    //! @brief Lua�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_LuaStateManager::C_LuaManagerStateImpl
    {
    public:
        C_LuaManagerStateImpl();                                                                 // �R���X�g���N�^
        ~C_LuaManagerStateImpl();                                                                // �f�X�g���N�^
        void Create(const std::string& rId);                                                // Lua�X�e�[�g���쐬
        void Destroy(const std::string& rId);                                               // Lua�X�e�[�g��j��
        void AllDestroy();                                                                  // Lua�X�e�[�g��S�Ĕj��
        void PrintStack(const std::string& rId);                                            // �X�^�b�N���o��
        boost::optional<const LuaStatePtr&> GetState(const std::string& rId) const;         // Lua�X�e�[�g���擾
    private:
        std::unordered_map<std::string, LuaStatePtr> pStates_;                              ///< @brief Lua�X�e�[�g
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LuaStateManager::C_LuaManagerStateImpl::C_LuaManagerStateImpl()
    {
        // �S�̂Ŏg�p����Lua�X�e�[�g���쐬
        Create(ID::s_pGLOBAL);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LuaStateManager::C_LuaManagerStateImpl::~C_LuaManagerStateImpl()
    {
        if (pStates_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g���쐬����
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::Create(const std::string& rId)
    {
        // ���ɓ���ID�ō쐬���Ă���ꍇ
        if (pStates_.find(rId) != pStates_.end())
        {
            std::cout << "[ C_LuaManagerStateImpl::Create ] : ���ɓ���ID��Lua�X�e�[�g���쐬���Ă��܂��B" << std::endl;
            std::cout << "                          ID : " << rId << std::endl;

            return;
        }

        // Lua�X�e�[�g���쐬
        pStates_[rId].reset(::luaL_newstate(), [](lua_State* pState){ ::lua_close(pState); });

        // �W�����C�u�������g�p�\�ɂ���
        ::luaL_openlibs(pStates_[rId].get());

        // Luabind���J��
        ::luabind::open(pStates_[rId].get());
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g��j������
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::Destroy(const std::string& rId)
    {
        // Lua�X�e�[�g���쐬����Ă��Ȃ��ꍇ
        if (pStates_.find(rId) == pStates_.end())
        {
            std::cout << "[ C_LuaManagerStateImpl::PrintStack ] : Lua�X�e�[�g���쐬����Ă��܂���B" << std::endl;

            return;
        }

        // �v�f���폜
        pStates_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g��S�Ĕj������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::AllDestroy()
    {
        pStates_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �X�^�b�N���o�͂���
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::PrintStack(const std::string& rId)
    {
        // Lua�X�e�[�g���쐬����Ă��Ȃ��ꍇ
        if (pStates_.find(rId) == pStates_.end())
        {
            std::cout << "[ C_LuaManagerStateImpl::PrintStack ] : Lua�X�e�[�g���쐬����Ă��܂���B" << std::endl;

            return;
        }

        // �X�^�b�N�����擾
        const int32_t STACK_NUMBER = ::lua_gettop(pStates_[rId].get());

        if (STACK_NUMBER == 0)
        {
            std::cout << "[ C_LuaManagerStateImpl::PrintStack ] : �X�^�b�N�ɉ����ς܂�Ă��܂���B" << std::endl;

            return;
        }

        for (int32_t i = STACK_NUMBER; i >= 1; i--)
        {
            std::printf("%03d(%04d): ", i, -STACK_NUMBER + i - 1);

            // �^�C�v���擾
            int32_t type = ::lua_type(pStates_[rId].get(), i);

            // �^�C�v����ǂ̃f�[�^���ς܂�Ă���̂����f����
            switch (type)
            {
            /* nil */
            case LUA_TNIL:

                std::printf("NIL\n");

                break;
            /* �u�[���A�� */
            case LUA_TBOOLEAN:

                std::printf("BOOLEAN %s\n", ::lua_toboolean(pStates_[rId].get(), i) ? "true" : "false");

                break;
            /* �y�ʃ��[�U�[�f�[�^ */
            case LUA_TLIGHTUSERDATA:

                std::printf("LIGHTUSERDATA\n");

                break;
            /* ���� */
            case LUA_TNUMBER:

                std::printf("NUMBER %f\n", ::lua_tonumber(pStates_[rId].get(), i));

                break;
            /* ������ */
            case LUA_TSTRING:

                std::printf("STRING %s\n", lua_tostring(pStates_[rId].get(), i));

                break;
            /* �e�[�u�� */
            case LUA_TTABLE:

                std::printf("TABLE\n");

                break;
            /* �֐� */
            case LUA_TFUNCTION:

                std::printf("FUNCTION\n");

                break;
            /* ���[�U�[�f�[�^ */
            case LUA_TUSERDATA:

                std::printf("USERDATA\n");

                break;
            /* �X���b�h */
            case LUA_TTHREAD:

                std::printf("THREAD\n");

                break;
            }
        }

        std::printf("-----------------------------\n\n");
    }


    /*************************************************************//**
     *
     *  @brief  Lua�X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return Lua�X�e�[�g
     *
     ****************************************************************/
    boost::optional<const LuaStatePtr&> C_LuaStateManager::C_LuaManagerStateImpl::GetState(const std::string& rId) const
    {
        auto iterator = pStates_.find(rId);
        if (iterator == pStates_.end()) return boost::none;

        return (*iterator).second;
    }
}