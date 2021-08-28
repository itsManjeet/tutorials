#include <bits/stdc++.h>
using namespace std;

#include "decoder.hh"
#include "encoder.hh"

#define FIXED_DELAY(delay) delay / 10

#define ENABLE_BENCHMARK

#ifdef ENABLE_BENCHMARK
#define BENCHMARK(statement, message)                                                             \
    {                                                                                             \
        auto start = chrono::system_clock::now();                                                 \
        statement;                                                                                \
        auto end = chrono::system_clock::now();                                                   \
        cout << message << " : "                                                                  \
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl; \
    }
#else
#define BENCHMARK(statement, message) statement;
#endif

int main(int ac, char **av)
{
    bob::GifDecoder decoder;
    GifWriter encoder;

    if (ac <= 1)
    {
        cerr << "Usage: [input-gif] [output-gif]" << endl;
        return 1;
    }

    decoder.load(av[1]);

    BENCHMARK(
        {
            GifBegin(&encoder, "output.gif", decoder.getWidth(),
                     decoder.getHeight(), FIXED_DELAY(decoder.getDelay(0)));

            for (int i = 0; i < decoder.getFrameCount(); i++)
            {
                auto data = decoder.getFrame(i);
                BENCHMARK(GifWriteFrame(&encoder, reinterpret_cast<const uint8_t *>(data), decoder.getWidth(),
                                        decoder.getHeight(), FIXED_DELAY(decoder.getDelay(i)));
                          , "  Frame: " + to_string(i));
            }

            GifEnd(&encoder);
        },
        "Total")
}