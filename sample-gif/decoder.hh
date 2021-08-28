#pragma once

#include <vector>
#include <map>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

namespace bob
{
    class GifDataBlock
    {
    private:
        const uint8_t *data;
        int32_t remain;

    public:
        GifDataBlock(const uint8_t *data, int32_t remain)
            : remain(remain), data(data)
        {
        }
        ~GifDataBlock(void)
        {
        }
        bool read(uint8_t *dst, int32_t size)
        {
            if (remain < size)
            {
                return false;
            }
            memcpy(dst, data, size);

            data += size;
            remain -= size;
            return true;
        }
        bool read(uint16_t *dst)
        {
            return read((uint8_t *)dst, 2);
        }
    };

    class GifFrame
    {
    public:
        GifFrame(uint32_t *data, int32_t delayMs)
            : data{data}, delayMs(delayMs)
        {
        }
        ~GifFrame(void)
        {
        }

        const uint32_t *data;
        const int32_t delayMs;
    };

    class GifDecoder
    {
    private:
        static const int32_t MAX_STACK_SIZE = 4096;

        std::vector<GifFrame> frames;
        uint16_t width;
        uint16_t height;
        bool interlace;
        bool gctFlag;
        uint32_t gctSize;
        uint8_t bgIndex;
        uint8_t pixelAspect;
        uint32_t gct[256]; // [0] ->r, [1] -> g, [2] -> b, max size to avoid bounds checks
        uint8_t block[256];
        uint16_t ix, iy, iw, ih;
        uint32_t bgColor;
        uint32_t dispose;  // 0=no action; 1=leave in place; 2=restore to bg; 3=restore to prev
        bool transparency; // use transparent color
        uint16_t delay;
        uint8_t transIndex;
        int32_t frameCount;
        uint8_t *pixels;

        uint32_t lastDispose;
        uint16_t lrx, lry, lrw, lrh;
        uint32_t lastBgColor;
        uint32_t *image;
        const uint32_t *lastBitmap;

        std::vector<uint32_t> gctVector;
        std::map<uint32_t, uint8_t> gctIndexMap; // Maps color to index

        void init();
        bool readLSD(GifDataBlock *dataBlock);
        bool readColorTable(GifDataBlock *dataBlock, uint32_t *colorTable, int32_t ncolors);
        bool readHeader(GifDataBlock *dataBlock);
        bool readContents(GifDataBlock *dataBlock);
        bool skip(GifDataBlock *dataBlock);
        bool readBlock(GifDataBlock *dataBlock, uint8_t *blockSize);
        bool readNetscapeExt(GifDataBlock *dataBlock);
        bool readGraphicControlExt(GifDataBlock *dataBlock);
        bool readBitmap(GifDataBlock *dataBlock);
        void resetFrame();
        bool decodeBitmapData(GifDataBlock *dataBlock);
        void setPixels(uint32_t *act);

    public:
        GifDecoder(void);
        ~GifDecoder(void);
        bool load(const char *fileName);
        bool loadFromMemory(const uint8_t *data, uint32_t size);
        uint32_t getFrameCount();
        const uint32_t *getFrame(int32_t n);
        uint32_t getDelay(int32_t n);
        uint32_t getWidth();
        uint32_t getHeight();
        std::vector<uint32_t> getGCT();
        std::map<uint32_t, uint8_t> getGCTIndexMap();
    };
}