/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../ObjDefine.h"


//-------------------------------------------------------------
//!
//! @brief ���f��
//! @brief ���f���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief OBJ
    //! @brief OBJ�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace OBJ
    {
        //-------------------------------------------------------------
        //!
        //! @brief OBJ���[�_�[
        //! @brief OBJ�t�@�C���̃p�[�X���s���N���X
        //!
        //-------------------------------------------------------------
        class C_ObjLoader
        {
        public:
            C_ObjLoader();                                                                              // �R���X�g���N�^
            ~C_ObjLoader();                                                                             // �f�X�g���N�^
            void Load(const std::string& rFilePath);                                                    // ���[�h����
            void Release();                                                                             // �������
            const S_Mesh& GetMesh() const;                                                              // ���b�V�����擾
            uint32_t GetMaterialCount() const;                                                          // �}�e���A�������擾
            int32_t GetMaterialIndex(const std::string& rName) const;                                   // �}�e���A���C���f�b�N�X���擾
            const S_Material& GetMaterial(int32_t index) const;                                         // �}�e���A�����擾
            const S_Material& GetMaterial(const std::string& rName) const;                              // �}�e���A�����擾
        private:
            /* �O���錾 */
            class C_ObjLoaderImpl;

            std::unique_ptr<C_ObjLoaderImpl> upImpl_;                                                   ///< @brief �������
        };
    }
}