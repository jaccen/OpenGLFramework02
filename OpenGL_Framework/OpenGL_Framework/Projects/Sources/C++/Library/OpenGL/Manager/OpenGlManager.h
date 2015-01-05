/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../OpenGlDefine.h"
#include "../../Window/Window/BaseWindow.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    namespace
    {
        /* �����_�����O�R���e�L�X�g��ID */
        namespace RenderingContextID
        {
            const char* s_pMAIN = "MainRenderingContext";
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief OpenGL�}�l�[�W���[
    //! @brief OpenGL���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_OpenGlManager : public Singleton::C_Singleton<C_OpenGlManager>
    {
        friend C_Singleton<C_OpenGlManager>;                                                                        // �V���O���g���N���X���t�����h��
    public:
        bool Initialize(const Window::C_BaseWindow& rMainWindow);                                                   // ����������
        bool InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,                                        // JSON�t�@�C���ŏ���������
                                    const std::string& rFilePath);
        void Finalize();                                                                                            // �I������
        bool CreateRenderingContext(const std::string& rId);                                                        // �����_�����O�R���e�L�X�g���쐬
        void DestroyRenderingContext(const std::string& rId);                                                       // �����_�����O�R���e�L�X�g��j��
        void AllDestroyRenderingContext();                                                                          // �S�Ẵ����_�����O�R���e�L�X�g��j��
        bool SetCurrentRenderingContext(const std::string& rId = RenderingContextID::s_pMAIN);                      // �����_�����O�R���e�L�X�g���J�����g�ɐݒ�
        void ResetCurrentRenderingContext();                                                                        // �J�����g�̃����_�����O�R���e�L�X�g�����Z�b�g
        void ClearBackBuffer(float red = 0.0f,                                                                      // �o�b�N�o�b�t�@���N���A
                             float green = 0.0f,
                             float blue = 0.0f,
                             float alpha = 0.0f,
                             BufferBitFlag bufferClearFlag = Buffer::Pixel::s_COLOR | Buffer::Pixel::s_DEPTH);
        void SwapBuffer();                                                                                          // �o�b�t�@�̓���ւ�
        void SetViewport(int32_t positionX,                                                                         // �r���[�|�[�g�̐ݒ�
                         int32_t positionY,
                         int32_t width,
                         int32_t height);
        void EnableColorMask(bool redValidFlag = true,                                                              // �J���[�}�X�N��L����
                             bool greenValidFlag = true,
                             bool blueValidFlag = true,
                             bool alphaValidFlag = true);
        void EnableDepthTest(bool validFlag = true);                                                                // �[�x�e�X�g�̗L����
        void EnableDepthMask(bool validFlag = true);                                                                // �[�x�}�X�N�̗L����
        void EnableStencilTest(bool validFlag = true);                                                              // �X�e���V���e�X�g��L����
        void EnableStencilMask(bool validFlag = true);                                                              // �X�e���V���}�X�N��L����
        void EnableMultiSample(bool validFlag = true);                                                              // �}���`�T���v���̗L����
        void EnableBlend(bool validFlag = true);                                                                    // �u�����h�̗L����
        void EnableCulling(bool validFlag = true);                                                                  // �J�����O�̗L����
        void EnableRasterrizerDiscard(bool validFlag = true);                                                       // ���X�^���C�U�̒�~��L����
        void EnableShaderProgramPointSize(bool balidFlag = true);                                                   // �V�F�[�_�[�v���O�����ł̓_�̃T�C�Y��L����
        void SetBlendFunction(BlendEnum sourceFactor = BlendFactor::s_ALL_ONE,                                      // �u�����h�̊֐���ݒ�
                              BlendEnum destinationFactor = BlendFactor::s_ALL_ZERO);
        void SetCullingFace(FaceEnum face = Face::s_BACK);                                                          // �J�����O������ʂ�ݒ�
        void SetStencilClearValue(int32_t clearValue = 0);                                                          // �X�e���V���̃N���A�l��ݒ�
        void SetStencilFunction(StencilEnum frontFaceFunction,                                                      // �X�e���V���̊֐���ݒ�
                                StencilEnum backFaceFunction,
                                int32_t comparisonValue,
                                uint32_t mask = ~0);
        void SetStencilProcess(StencilEnum stencilFail,                                                             // �X�e���V���̏�����ݒ�
                               StencilEnum stencilPassAndDepthFail,
                               StencilEnum stencilPassAndDepthPass,
                               FaceEnum face = Face::s_BOTH);
        void DrawPrimitive(PrimitiveEnum primitive,                                                                 // �v���~�e�B�u��`��
                           VertexArrayObjectHandle vertexArrayObjectHandle,
                           int32_t vertexCount,
                           int32_t firstVertexNumber = 0);
        void DrawPrimitiveInstanced(PrimitiveEnum primitive,                                                        // �v���~�e�B�u��`��
                                    VertexArrayObjectHandle vertexArrayObjectHandle,                                // �v���~�e�B�u���C���X�^���V���O�`��
                                    int32_t vertexCount,
                                    int32_t instanceCount,
                                    int32_t firstVertexNumber = 0);
        void DrawPrimitiveWithIndices(PrimitiveEnum primitive,                                                      // �C���f�b�N�X��p���ăv���~�e�B�u��`��
                                      VertexArrayObjectHandle vertexArrayObjectHandle,
                                      IndexBufferObjenctHandle indexBufferObjectHandle,
                                      DataEnum indexDataType,
                                      int32_t indexCount);
        void DrawPrimitiveInstancedWithIndices(PrimitiveEnum primitive,                                             // �C���f�b�N�X��p���ăv���~�e�B�u���C���X�^���V���O�`��
                                               VertexArrayObjectHandle vertexArrayObjectHandle,
                                               IndexBufferObjenctHandle indexBufferObjectHandle,
                                               DataEnum indexDataType,
                                               int32_t indexCount,
                                               int32_t instanceCount);
    private:
        /* �O���錾 */
        class C_OpenGlManagerImpl;

        std::unique_ptr<C_OpenGlManagerImpl> upImpl_;                                                               ///< @brief �������

        C_OpenGlManager();                                                                                          // �R���X�g���N�^
        ~C_OpenGlManager() override;                                                                                // �f�X�g���N�^
    };
}