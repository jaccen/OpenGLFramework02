/* �w�b�_�t�@�C�� */
#include "PrimitiveBuffer.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{

    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PrimitiveBuffer::~C_PrimitiveBuffer()
    {
        glDeleteBuffers(1, &vertexBufferObjectHandle_);
        glDeleteBuffers(1, &indexBufferObjectHandle_);
        glDeleteVertexArrays(1, &vertexArrayObjectHandle_);
    }


    /*************************************************************//**
     *
     *  @brief  ���_�z��I�u�W�F�N�g�n���h�����擾����
     *  @param  �Ȃ�
     *  @return ���_�z��I�u�W�F�N�g�n���h��
     *
     ****************************************************************/
    VertexArrayObjectHandle C_PrimitiveBuffer::GetVertexArrayObjectHandle() const
    {
        return vertexArrayObjectHandle_;
    }


    /*************************************************************//**
     *
     *  @brief  �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�n���h�����擾����
     *  @param  �Ȃ�
     *  @return �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�n���h��
     *
     ****************************************************************/
    VertexArrayObjectHandle C_PrimitiveBuffer::GetIndexBufferObjectHandle() const
    {
        return indexBufferObjectHandle_;
    }


    /*************************************************************//**
     *
     *  @brief  ���_�����擾����
     *  @param  �Ȃ�
     *  @return ���_��
     *
     ****************************************************************/
    uint32_t C_PrimitiveBuffer::GetVertexCount() const
    {
        return vertexCount_;
    }


    /*************************************************************//**
     *
     *  @brief  �C���f�b�N�X�����擾����
     *  @param  �Ȃ�
     *  @return �C���f�b�N�X��
     *
     ****************************************************************/
    uint32_t C_PrimitiveBuffer::GetIndexCount() const
    {
        return indexCount_;
    }
}

