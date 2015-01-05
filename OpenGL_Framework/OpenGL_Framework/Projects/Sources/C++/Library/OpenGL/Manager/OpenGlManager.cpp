/* �w�b�_�t�@�C�� */
#include "OpenGlManagerImpl.h"


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
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OpenGlManager::C_OpenGlManager() :

        // �������
        upImpl_(std::make_unique<C_OpenGlManagerImpl>(this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OpenGlManager::~C_OpenGlManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  ���C���E�B���h�E
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::Initialize(const Window::C_BaseWindow& rMainWindow)
    {
        if (upImpl_->Initialize(rMainWindow) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  JSON�t�@�C���ŏ������������s��
     *  @param  ���C���E�B���h�E
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,
                                                 const std::string& rFilePath)
    {
        if (upImpl_->InitializeWithJsonFile(rMainWindow, rFilePath) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g���쐬����
     *  @param  ID
     *  @return ����I���Ftrue �E �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::CreateRenderingContext(const std::string& rId)
    {
        if (upImpl_->CreateRenderingContext(rId) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g��j������
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::DestroyRenderingContext(const std::string& rId)
    {
        upImpl_->DestroyRenderingContext(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ����_�����O�R���e�L�X�g��j������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::AllDestroyRenderingContext()
    {
        upImpl_->AllDestroyRenderingContext();
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g���J�����g�ɐݒ肷��
     *  @param  ID
     *  @return ����I���Ftrue �E �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::SetCurrentRenderingContext(const std::string& rId)
    {
        if (upImpl_->SetCurrentRenderingContext(rId) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �J�����g�̃����_�����O�R���e�L�X�g�����Z�b�g����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::ResetCurrentRenderingContext()
    {
        upImpl_->ResetCurrentRenderingContext();
    }


    /*************************************************************//**
     *
     *  @brief  �o�b�N�o�b�t�@�̃N���A���s��
     *  @param  �N���A�J���[�̐�
     *  @param  �N���A�J���[�̗�
     *  @param  �N���A�J���[�̐�
     *  @param  �N���A����̃A���t�@
     *  @param  �o�b�t�@�̃N���A�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::ClearBackBuffer(float red,
                                          float green,
                                          float blue,
                                          float alpha,
                                          BufferBitFlag bufferClearFlag)
    {
        // �o�b�N�o�b�t�@���N���A����F��ݒ�
        ::glClearColor(red, green, blue, alpha);

        // �o�b�N�o�b�t�@���N���A
        ::glClear(bufferClearFlag);
    }


    /*************************************************************//**
     *
     *  @brief  �o�b�t�@�̓���ւ����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SwapBuffer()
    {
        upImpl_->SwapBuffer();
    }


    /*************************************************************//**
     *
     *  @brief  �r���[�|�[�g�̐ݒ���s��
     *  @param  �r���[��( ���[ )X���W
     *  @param  �r���[��( ��[ )Y���W
     *  @param  �r���[�̕�
     *  @param  �r���[�̍���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SetViewport(int32_t positionX,
                                      int32_t positionY,
                                      int32_t width,
                                      int32_t height)
    {
        // �r���[�|�[�g�̐ݒ�
        ::glViewport(positionX, positionY, width, height);
    }


    /*************************************************************//**
     *
     *  @brief  �J���[�}�X�N��L��������
     *  @param  �Ԃ��L�������f����t���O
     *  @param  �΂��L�������f����t���O
     *  @param  ���L�������f����t���O
     *  @param  �A���t�@���L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableColorMask(bool redValidFlag,
                                          bool greenValidFlag,
                                          bool blueValidFlag,
                                          bool alphaValidFlag)
    {
        static auto s_ChangeGlBoolean = [](bool validFlag){ return (validFlag == true) ? GL_FALSE : GL_TRUE; };

        ::glColorMask(s_ChangeGlBoolean(redValidFlag),
                      s_ChangeGlBoolean(greenValidFlag),
                      s_ChangeGlBoolean(blueValidFlag),
                      s_ChangeGlBoolean(alphaValidFlag));
    }

    /*************************************************************//**
     *
     *  @brief  �[�x�e�X�g��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableDepthTest(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_DEPTH_TEST) : ::glDisable(GL_DEPTH_TEST);
    }


    /*************************************************************//**
     *
     *  @brief  �[�x�}�X�N��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableDepthMask(bool validFlag)
    {
        (validFlag == true) ? ::glDepthMask(GL_FALSE) : ::glDepthMask(GL_TRUE);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e���V���e�X�g��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableStencilTest(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_STENCIL_TEST) : ::glDisable(GL_STENCIL_TEST);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e���V���}�X�N��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableStencilMask(bool validFlag)
    {
        (validFlag == true) ? ::glStencilMask(GL_FALSE) : ::glStencilMask(GL_TRUE);
    }


    /*************************************************************//**
     *
     *  @brief  �}���`�T���v����L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableMultiSample(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_MULTISAMPLE) : ::glDisable(GL_MULTISAMPLE);
    }


    /*************************************************************//**
     *
     *  @brief  �u�����h��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableBlend(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_BLEND) : ::glDisable(GL_BLEND);
    }


    /*************************************************************//**
     *
     *  @brief  �J�����O��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableCulling(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_CULL_FACE) : ::glDisable(GL_CULL_FACE);
    }


    /*************************************************************//**
     *
     *  @brief  ���X�^���C�U�̒�~��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableRasterrizerDiscard(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_RASTERIZER_DISCARD) : ::glDisable(GL_RASTERIZER_DISCARD);
    }


    /*************************************************************//**
     *
     *  @brief  �V�F�[�_�[�v���O�����ł̓_�̃T�C�Y��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::EnableShaderProgramPointSize(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_PROGRAM_POINT_SIZE) : ::glDisable(GL_PROGRAM_POINT_SIZE);
    }


    /*************************************************************//**
     *
     *  @brief  �u�����h�̊֐��̐ݒ���s��
     *  @param  �V�����F�̗v�f
     *  @param  ���݂̐F�̗v�f
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SetBlendFunction(BlendEnum sourceFactor,
                                           BlendEnum destinationFactor)
    {
        ::glBlendFunc(sourceFactor, destinationFactor);
    }


    /*************************************************************//**
     *
     *  @brief  �J�����O����ʂ̐ݒ���s��
     *  @param  ��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SetCullingFace(FaceEnum face)
    {
        ::glCullFace(face);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e���V���̃N���A�l�̐ݒ���s��
     *  @param  �X�e���V���̃N���A�l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SetStencilClearValue(int32_t clearValue)
    {
        ::glClearStencil(clearValue);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e���V���̊֐��̐ݒ���s��
     *  @param  �\�ʂ̊֐�
     *  @param  ���ʂ̊֐�
     *  @param  ��r�l
     *  @param  �}�X�N
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SetStencilFunction(StencilEnum frontFaceFunction,
                                             StencilEnum backFaceFunction,
                                             int32_t comparisonValue,
                                             uint32_t mask)
    {
        glStencilFuncSeparate(frontFaceFunction, backFaceFunction, comparisonValue, mask);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e���V���̊֐��̐ݒ���s��
     *  @param  �֐��̎��
     *  @param  ��r�l
     *  @param  �}�X�N
     *  @param  ��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::SetStencilProcess(StencilEnum stencilFail,
                                            StencilEnum stencilPassAndDepthFail,
                                            StencilEnum stencilPassAndDepthPass,
                                            FaceEnum face)
    {
        glStencilOpSeparate(face, stencilFail, stencilPassAndDepthFail, stencilPassAndDepthPass);
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�̕`����s��
     *  @param  �v���~�e�B�u�̎��
     *  @param  ���_�z��I�u�W�F�N�g�n���h��
     *  @param  ���_��
     *  @param  �`����J�n����ŏ��̒��_�ԍ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitive(PrimitiveEnum primitive,
                                        VertexArrayObjectHandle vertexArrayObjectHandle,
                                        int32_t vertexCount,
                                        int32_t firstVertexNumber)
    {
        assert(vertexArrayObjectHandle != 0);

        glBindVertexArray(vertexArrayObjectHandle);
        ::glDrawArrays(primitive, firstVertexNumber, vertexCount);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�̃C���X�^���V���O�`����s��
     *  @param  �v���~�e�B�u�̎��
     *  @param  ���_�z��I�u�W�F�N�g�n���h��
     *  @param  ���_��
     *  @param  �C���X�^���X��
     *  @param  �`����J�n����ŏ��̒��_�ԍ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitiveInstanced(PrimitiveEnum primitive,
                                                 VertexArrayObjectHandle vertexArrayObjectHandle,
                                                 int32_t vertexCount,
                                                 int32_t instanceCount,
                                                 int32_t firstVertexNumber)
    {
        assert(vertexArrayObjectHandle != 0);

        glBindVertexArray(vertexArrayObjectHandle);
        ::glDrawArraysInstanced(primitive, firstVertexNumber, vertexCount, instanceCount);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  �C���f�b�N�X��p���ăv���~�e�B�u�̕`����s��
     *  @param  �v���~�e�B�u�̎��
     *  @param  ���_�z��I�u�W�F�N�g�n���h��
     *  @param  �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�n���h��
     *  @param  �C���f�b�N�X�̃f�[�^�^
     *  @param  �C���f�b�N�X��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitiveWithIndices(PrimitiveEnum primitive,
                                                   VertexArrayObjectHandle vertexArrayObjectHandle,
                                                   IndexBufferObjenctHandle indexBufferObjectHandle,
                                                   DataEnum indexDataType,
                                                   int32_t indexCount)
    {
        assert(vertexArrayObjectHandle != 0);
        assert(indexBufferObjectHandle != 0);
        
        glBindVertexArray(vertexArrayObjectHandle);
        glBindBuffer(Buffer::s_INDEX, indexBufferObjectHandle);

        const int32_t NO_USE_RAW_DATA_INDICES = 0;
        ::glDrawElements(primitive, indexCount, indexDataType, reinterpret_cast<GLubyte*>(NO_USE_RAW_DATA_INDICES));

        glBindBuffer(Buffer::s_INDEX, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  �C���f�b�N�X��p���ăv���~�e�B�u�̕`����s��
     *  @param  �v���~�e�B�u�̎��
     *  @param  ���_�z��I�u�W�F�N�g�n���h��
     *  @param  �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�n���h��
     *  @param  �C���f�b�N�X�̃f�[�^�^
     *  @param  �C���f�b�N�X��
     *  @param  �C���X�^���X��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitiveInstancedWithIndices(PrimitiveEnum primitive,
                                                            VertexArrayObjectHandle vertexArrayObjectHandle,
                                                            IndexBufferObjenctHandle indexBufferObjectHandle,
                                                            DataEnum indexDataType,
                                                            int32_t indexCount,
                                                            int32_t instanceCount)
    {
        assert(vertexArrayObjectHandle != 0);
        assert(indexBufferObjectHandle != 0);
        
        glBindVertexArray(vertexArrayObjectHandle);
        glBindBuffer(Buffer::s_INDEX, indexBufferObjectHandle);

        const int32_t NO_USE_RAW_DATA_INDICES = 0;
        ::glDrawElementsInstanced(primitive, indexCount, indexDataType, reinterpret_cast<GLubyte*>(NO_USE_RAW_DATA_INDICES), instanceCount);

        glBindBuffer(Buffer::s_INDEX, 0);
        glBindVertexArray(0);
    }
}