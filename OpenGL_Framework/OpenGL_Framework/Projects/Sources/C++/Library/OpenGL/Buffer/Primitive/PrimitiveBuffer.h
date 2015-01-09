/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../OpenGlDefine.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* �O���錾 */
    class C_PrimitiveBuffer;

    
    using PrimitiveBufferPtr = std::shared_ptr<C_PrimitiveBuffer>;                                  // PrimitiveBufferPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �v���~�e�B�u�o�b�t�@
    //! @brief �v���~�e�B�u�`��ɗp����o�b�t�@��\���N���X
    //!
    //-------------------------------------------------------------
    class C_PrimitiveBuffer
    {
    public:
        /* ������� */
        template<typename T, typename U>
        struct S_CreateData
        {
            T* pVertices_ = nullptr;                                                                ///< @brief ���_
            uint32_t vertexCount_ = 0;                                                              ///< @brief ���_��
            uint32_t vertexAttributeCount_ = 0;                                                     ///< @brief ���_�̑�����
            uint32_t* vertexAttributeElementCountList_ = nullptr;                                   ///< @brief ���_�̑����̗v�f�����X�g
            DataEnum* vertexAttributeDataTypeList_ = nullptr;                                       ///< @brief ���_�̑����̃f�[�^�^���X�g
            ModifyEnum vertexModifyType_ = 0;                                                       ///< @brief ���_�̏C���̎��
            U* pIndices_ = nullptr;                                                                 ///< @brief �C���f�b�N�X
            uint32_t indexCount_ = 0;                                                               ///< @brief �C���f�b�N�X��
            ModifyEnum indexModifyType_ = Modify::s_STATIC;                                         ///< @brief �C���f�b�N�X�̏C���̎��
        };

        template<typename T, typename U = uint16_t>
        C_PrimitiveBuffer(T* pVertices,                                                             // �R���X�g���N�^
                          uint32_t vertexCount,
                          uint32_t vertexAttributeCount,
                          uint32_t vertexAttributeElementCountList[],
                          DataEnum vertexAttributeDataTypeList[],
                          ModifyEnum vertexModifyType,
                          U* pIndices = nullptr,
                          uint32_t indexCount = 0,
                          ModifyEnum indexModifyType = Modify::s_STATIC);
        template<typename T, typename U = uint16_t>
        C_PrimitiveBuffer(const S_CreateData<T, U>& rCreateData);                                   // �R���X�g���N�^
        virtual ~C_PrimitiveBuffer();                                                               // �f�X�g���N�^
        VertexArrayObjectHandle GetVertexArrayObjectHandle() const;                                 // ���_�z��I�u�W�F�N�g�n���h�����擾
        IndexBufferObjenctHandle GetIndexBufferObjectHandle() const;                                // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�n���h�����擾
        uint32_t GetVertexCount() const;                                                            // ���_�����擾
        uint32_t GetIndexCount() const;                                                             // �C���f�b�N�X�����擾
        template<typename T>
        void RewriteVertices(T vertices[],                                                          // ���_�̏�������
                             int32_t rewriteVertexCount,
                             int32_t firstVertexNumber = 0);   
        template<typename T>
        void RewriteIndices(T indices[],                                                            // �C���f�b�N�X�̏�������
                            int32_t rewriteIndexCount,
                            int32_t firstIndexNumber = 0);
        template<typename T, typename U = uint16_t>
        static PrimitiveBufferPtr s_Create(T* pVertices,                                            // ��������
                                           uint32_t vertexCount,
                                           uint32_t vertexAttributeCount,
                                           uint32_t vertexAttributeElementCountList[],
                                           DataEnum vertexAttributeDataTypeList[],
                                           ModifyEnum vertexModifyType,
                                           U* pIndices = nullptr,
                                           uint32_t indexCount = 0,
                                           ModifyEnum indexModifyType = Modify::s_STATIC);
        template<typename T, typename U = uint16_t>
        static PrimitiveBufferPtr s_Create(const S_CreateData<T, U>& rCreateData);                  // ��������
    private:
        VertexArrayObjectHandle vertexArrayObjectHandle_ = 0;                                       ///< @brief ���_�z��I�u�W�F�N�g�n���h��
        VertexBufferObjectHandle vertexBufferObjectHandle_ = 0;                                     ///< @brief ���_�o�b�t�@�I�u�W�F�N�g�n���h��
        IndexBufferObjenctHandle indexBufferObjectHandle_ = 0;                                      ///< @brief �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�n���h��
        uint32_t vertexCount_ = 0;                                                                  ///< @brief ���_��
        uint32_t indexCount_ = 0;                                                                   ///< @brief �C���f�b�N�X��
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ���_
     *  @param  ���_��
     *  @param  ���_�̑�����
     *  @param  ���_�̑����̗v�f���̃��X�g
     *  @param  ���_�̑����̌^�̃��X�g
     *  @param  ���_�̏C���̎��
     *  @param  �C���f�b�N�X
     *  @param  �C���f�b�N�X��
     *  @param  �C���f�b�N�X�̏C���̎��
     *
     ****************************************************************/
    template<typename T, typename U>
    C_PrimitiveBuffer::C_PrimitiveBuffer(T* pVertices,
                                         uint32_t vertexCount,
                                         uint32_t vertexAttributeCount,
                                         uint32_t vertexAttributeElementCountList[],
                                         DataEnum vertexAttributeDataTypeList[],
                                         ModifyEnum vertexModifyType,
                                         U* pIndices,
                                         uint32_t indexCount,
                                         ModifyEnum indexModifyType) :

        // ���_�ƃC���f�b�N�X��
        vertexCount_(vertexCount),
        indexCount_(indexCount)

    {
        // ���_�o�b�t�@�I�u�W�F�N�g�ƃC���f�b�N�X�o�b�t�@�I�u�W�F�N�g���쐬
        glGenBuffers(1, &vertexBufferObjectHandle_);
        glGenBuffers(1, &indexBufferObjectHandle_);

        // ���_�o�b�t�@���o�C���h���A�S�Ẵf�[�^��]��
        glBindBuffer(Buffer::s_VERTEX, vertexBufferObjectHandle_);
        glBufferData(Buffer::s_VERTEX, vertexCount * sizeof(T), pVertices, vertexModifyType);

        // ���_�z��I�u�W�F�N�g���쐬�ƃo�C���h
        glGenVertexArrays(1, &vertexArrayObjectHandle_);
        glBindVertexArray(vertexArrayObjectHandle_);

        // �o�C�g�I�t�Z�b�g
        int32_t byteOffset = 0;

        for (size_t i = 0; i < vertexAttributeCount; ++i)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, vertexAttributeElementCountList[i], vertexAttributeDataTypeList[i], GL_FALSE, sizeof(T), reinterpret_cast<GLubyte*>(byteOffset));

            if (DataType::s_DOUBLE == vertexAttributeDataTypeList[i])
            {
                byteOffset += vertexAttributeElementCountList[i] * 8;
            }
            else if (DataType::s_BOOL == vertexAttributeDataTypeList[i])
            {
                byteOffset += vertexAttributeElementCountList[i] * 1;
            }
            else
            {
                byteOffset += vertexAttributeElementCountList[i] * 4;
            }
        }

        if (pIndices)
        {
            // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g���o�C���h���f�[�^��]��
            glBindBuffer(Buffer::s_INDEX, indexBufferObjectHandle_);
            glBufferData(Buffer::s_INDEX, indexCount * sizeof(U), pIndices, indexModifyType);
        }

        // �e�o�b�t�@���A���o�C���h
        glBindBuffer(Buffer::s_VERTEX, 0);
        glBindBuffer(Buffer::s_VERTEX, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �������
     *
     ****************************************************************/
    template<typename T, typename U>
    C_PrimitiveBuffer::C_PrimitiveBuffer(const S_CreateData<T, U>& rCreateData) : C_PrimitiveBuffer(rCreateData.pVertices_,
                                                                                                    rCreateData.vertexCount_,
                                                                                                    rCreateData.vertexAttributeCount_,
                                                                                                    rCreateData.vertexAttributeElementCountList_,
                                                                                                    rCreateData.vertexAttributeDataTypeList_,
                                                                                                    rCreateData.vertexModifyType_,
                                                                                                    rCreateData.pIndices_,
                                                                                                    rCreateData.indexCount_,
                                                                                                    rCreateData.indexModifyType_)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���_�̏����������s��
     *  @param  ���_
     *  @param  ���������钸�_��
     *  @param  �擪�̒��_�ԍ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_PrimitiveBuffer::RewriteVertices(T vertices[],
                                            int32_t rewriteVertexCount,
                                            int32_t firstVertexNumber)
    {
        // ���_�o�b�t�@���o�C���h
        glBindBuffer(Buffer::s_VERTEX, vertexBufferObjectHandle_);

        // ���_�o�b�t�@���}�b�v
        T* pVertices = reinterpret_cast<T*>(glMapBuffer(Buffer::s_VERTEX, GL_WRITE_ONLY));
        assert(pVertices);

        // ���_�o�b�t�@�̃f�[�^����������
        int32_t loopTotalCount = firstVertexNumber + rewriteVertexCount;
        int32_t indexOfArgumentVertex = 0;

        for (int32_t i = firstVertexNumber; i < loopTotalCount; ++i)
        {
            pVertices[i] = vertices[indexOfArgumentVertex];
            ++indexOfArgumentVertex;
        }

        // ���_�o�b�t�@���A���}�b�v
        glUnmapBuffer(Buffer::s_VERTEX);

        // ���_�o�b�t�@���A���o�C���h
        glBindBuffer(Buffer::s_VERTEX, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �C���f�b�N�X�̏����������s��
     *  @param  �C���f�b�N�X
     *  @param  ����������C���f�b�N�X��
     *  @param  �擪�̃C���f�b�N�X�ԍ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void C_PrimitiveBuffer::RewriteIndices(T indices[],
                                           int32_t rewriteIndexCount,
                                           int32_t firstIndexNumber)
    {
        // �C���f�b�N�X�o�b�t�@���o�C���h
        glBindBuffer(Buffer::s_INDEX, vertexBufferObjectHandle_);

        // �C���f�b�N�X�o�b�t�@���}�b�v
        T* pIndices = reinterpret_cast<T*>(glMapBuffer(Buffer::s_INDEX, GL_WRITE_ONLY));
        assert(pVertices);

        // �C���f�b�N�X�o�b�t�@�̃f�[�^����������
        int32_t loopTotalCount = firstVertexNumber + rewriteVertexCount;
        int32_t indexOfArgumentIndex = 0;

        for (int32_t i = firstIndexNumber; i < loopTotalCount; ++i)
        {
            pIndices[i] = indices[indexOfArgumentIndex];
            ++indexOfArgumentIndex;
        }

        // �C���f�b�N�X�o�b�t�@���A���}�b�v
        glUnmapBuffer(Buffer::s_INDEX);

        // �C���f�b�N�X�o�b�t�@���A���o�C���h
        glBindBuffer(Buffer::s_INDEX, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ���_
     *  @param  ���_��
     *  @param  ���_�̑�����
     *  @param  ���_�̑����̗v�f���̃��X�g
     *  @param  ���_�̑����̌^�̃��X�g
     *  @param  ���_�̏C���̎��
     *  @param  �C���f�b�N�X
     *  @param  �C���f�b�N�X��
     *  @param  �C���f�b�N�X�̏C���̎��
     *  @return �|���S���o�b�t�@
     *
     ****************************************************************/
    template<typename T, typename U>
    PrimitiveBufferPtr C_PrimitiveBuffer::s_Create(T* pVertices,
                                                   uint32_t vertexCount,
                                                   uint32_t vertexAttributeCount,
                                                   uint32_t vertexAttributeElementCountList[],
                                                   DataEnum vertexAttributeDataTypeList[],
                                                   ModifyEnum vertexModifyType,
                                                   U* pIndices,
                                                   uint32_t indexCount,
                                                   ModifyEnum indexModifyType)
    {
        return std::make_shared<C_PrimitiveBuffer>(pVertices,
                                                   vertexCount,
                                                   vertexAttributeCount,
                                                   vertexAttributeElementCountList,
                                                   vertexAttributeDataTypeList,
                                                   vertexModifyType,
                                                   pIndices,
                                                   indexCount,
                                                   indexModifyType);
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  �������
     *  @return �|���S���o�b�t�@
     *
     ****************************************************************/
    template<typename T, typename U>
    PrimitiveBufferPtr C_PrimitiveBuffer::s_Create(const S_CreateData<T, U>& rCreateData)
    {
        return s_Create(rCreateData.pVertices_,
                        rCreateData.vertexCount_,
                        rCreateData.vertexAttributeCount_,
                        rCreateData.vertexAttributeElementCountList_,
                        rCreateData.vertexAttributeDataTypeList_,
                        rCreateData.vertexModifyType_,
                        rCreateData.pIndices_,
                        rCreateData.indexCount_,
                        rCreateData.indexModifyType_);
    }
}
