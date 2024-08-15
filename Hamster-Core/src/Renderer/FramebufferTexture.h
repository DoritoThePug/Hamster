//
// Created by jaden on 30/07/24.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

namespace Hamster {
    class FramebufferTexture {
    public:
        FramebufferTexture(unsigned int width, unsigned int height);

        void Bind();

        void Unbind();

        void ResizeFrameBuffer(unsigned int height, unsigned int widht);

        unsigned int GetTextureID();

    private:
        unsigned int m_ID;
        unsigned int m_TextureID;
        unsigned int m_RenderBufferID;
    };
} // Hamster

#endif //FRAMEBUFFER_H
