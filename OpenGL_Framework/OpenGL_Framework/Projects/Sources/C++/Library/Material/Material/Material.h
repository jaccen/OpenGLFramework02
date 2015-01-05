/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Math/Vector/Vector3.h"
#include "../../Texture/TextureDefine.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief �}�e���A��
//! @brief �}�e���A���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Material
{
    /* �O���錾 */
    struct S_Material;


    /* �ʖ� */
    using Vector3 = Math::S_Vector3<float>;                             // Vector3�^
    using MaterialPtr = std::shared_ptr<S_Material>;                    // MaterialPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �}�e���A��
    //! @brief �}�e���A���̊��\����
    //!
    //-------------------------------------------------------------
    struct S_Material
    {
        std::vector<Texture::TextureHandle> textureHandles_;            ///< @brief �e�N�X�`���n���h��
    };
}