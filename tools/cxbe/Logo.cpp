// ******************************************************************
// *
// *  This file is part of Cxbe
// *
// *  This program is free software; you can redistribute it and/or
// *  modify it under the terms of the GNU General Public License
// *  as published by the Free Software Foundation; either version 2
// *  of the License, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have received a copy of the GNU General Public License
// *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *  (c) 2021 Stefan Schmidt
// *
// *  All rights reserved
// *
// ******************************************************************
#include "Xbe.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

const uint08 defaultXbeLogo[] =
{
    0x8a, 0x02, 0x53, 0xd3, 0xc3, 0x05, 0xd5, 0x76, 0x01, 0x63,
    0xf3, 0xe3, 0x05, 0xf5, 0x76, 0x01, 0x63, 0xf3, 0xe3, 0x05,
    0xf5, 0x76, 0x01, 0x63, 0xf3, 0xe3, 0x05, 0xf5, 0xbe, 0x00,
    0x32, 0xb0, 0xa3, 0x43, 0x07, 0x93, 0xb5, 0x73, 0x0f, 0x33,
    0xa3, 0xb3, 0xa3, 0x43, 0x05, 0x63, 0xa3, 0x26, 0xb0, 0x63,
    0xf3, 0xe3, 0x05, 0xf5, 0x26, 0x00, 0x23, 0xa3, 0xb3, 0x93,
    0x8a, 0x00, 0x3a, 0xf0, 0x63, 0x05, 0x43, 0xd3, 0xf5, 0xa3,
    0x0b, 0x63, 0xe3, 0xf5, 0x83, 0x05, 0x93, 0x2e, 0xf0, 0x63,
    0xf3, 0xe3, 0x05, 0xf5, 0x22, 0x00, 0x33, 0xd3, 0xf5, 0x73,
    0x8a, 0x00, 0xf5, 0x2a, 0xb0, 0xd3, 0xf3, 0xd3, 0x09, 0xb3,
    0xf5, 0xd3, 0x33, 0x05, 0x93, 0xf5, 0xe3, 0x53, 0x07, 0xe3,
    0xf3, 0xd3, 0x26, 0xb0, 0x63, 0xf3, 0xe3, 0x05, 0xf5, 0x0f,
    0x33, 0xd3, 0xf5, 0x63, 0x8e, 0x00, 0xf5, 0x2a, 0x00, 0x63,
    0xf3, 0xe3, 0x0b, 0x83, 0xf5, 0xe3, 0x73, 0xc3, 0xf5, 0xc3,
    0x23, 0x09, 0xf5, 0x2a, 0x00, 0x63, 0xf3, 0xe3, 0x05, 0xf5,
    0x0d, 0x43, 0xe3, 0xf3, 0xe3, 0x63, 0x92, 0x00, 0xf5, 0x2a,
    0x00, 0x63, 0xf3, 0xe3, 0x0d, 0x53, 0xe3, 0xf9, 0x93, 0x0d,
    0xf5, 0x2a, 0x00, 0x63, 0xf3, 0xe3, 0x05, 0xf5, 0xdd, 0xf5,
    0xe3, 0x53, 0x96, 0x00, 0xf5, 0x2a, 0x00, 0x63, 0xf3, 0xe3,
    0x0f, 0x83, 0xf7, 0xd3, 0x23, 0x0d, 0xf5, 0x2a, 0x00, 0x63,
    0xf3, 0xe3, 0x05, 0x2a, 0xf0, 0xb3, 0x9a, 0x00, 0xf5, 0x2a,
    0x00, 0x63, 0xf3, 0xe3, 0x0d, 0xb3, 0xf5, 0xd3, 0xf5, 0xe3,
    0x53, 0x0b, 0xf5, 0x2a, 0x00, 0x63, 0xf3, 0xe3, 0x05, 0xf5,
    0x8d, 0xb3, 0xf5, 0xa3, 0x96, 0x00, 0xf5, 0x2a, 0x00, 0x63,
    0xf3, 0xe3, 0x09, 0x43, 0xd3, 0xf5, 0xb3, 0x03, 0x73, 0xe3,
    0xf5, 0x83, 0x09, 0xf5, 0x43, 0x26, 0x00, 0x63, 0xf3, 0xe3,
    0x05, 0xf5, 0x0f, 0xa3, 0xf5, 0xb3, 0x92, 0x00, 0xf5, 0x2a,
    0x00, 0x63, 0xf3, 0xe3, 0x07, 0x73, 0xe3, 0xf5, 0x83, 0x07,
    0x43, 0xd3, 0xf5, 0xb3, 0x07, 0xd3, 0x36, 0xf0, 0xe3, 0x05,
    0xf5, 0x22, 0x00, 0x93, 0xf5, 0xb3, 0x8e, 0x00, 0xf5, 0x2a,
    0x00, 0x63, 0xf3, 0xe3, 0x05, 0xa3, 0xf5, 0xe3, 0x53, 0x0d,
    0xb3, 0xf5, 0xd3, 0x43, 0x03, 0x43, 0xd3, 0x32, 0xf0, 0xe3,
    0x05, 0xf5, 0x26, 0x00, 0x93, 0xf5, 0xb3, 0x6a, 0x03,
};

// size, in bytes, of the default logo bitmap
const uint32 defaultXbeLogoSize = sizeof(defaultXbeLogo);

std::vector<uint08> Xbe::ImageToLogoBitmap (const std::vector<uint08> &raw)
{
    std::vector<uint08> bitmap;

    for (size_t i = 0; i < raw.size(); i++) {
        uint08 color = raw[i] >> 4;

        uint32 len = 1;

        while (i+1 < raw.size() && len < 1023 && color == raw[i+1] >> 4) {
            len++;
            i++;
        }

        LogoRLE rle;
        if (len < 8) {
            rle.m_Eight.bType1 = 1;
            rle.m_Eight.Len = len;
            rle.m_Eight.Data = color;
            bitmap.push_back(rle.m_Bytes[0]);
        } else {
            rle.m_Sixteen.bType1 = 0;
            rle.m_Sixteen.bType2 = 1;
            rle.m_Sixteen.Len = len;
            rle.m_Sixteen.Data = color;
            bitmap.push_back(rle.m_Bytes[0]);
            bitmap.push_back(rle.m_Bytes[1]);
        }
    }

    return bitmap;
}

static void skipWhitespace (std::ifstream &file)
{
    while (true) {
        char c = file.get();
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            file.unget();
            break;
        }
    }
}

static void skipComments (std::ifstream &file)
{
    skipWhitespace(file);

    while (true) {
        char c;

        if (!file.get(c).good())
            throw std::runtime_error("PGM file is corrupt");

        if (c != '#') {
            file.unget();
            break;
        }

        while (true) {
            file.get(c);
            if (c == '\r' || c == '\n') {
                skipWhitespace(file);
                break;
            }
        }
    }
}

static uint32 readUintAscii (std::ifstream &file)
{
    std::stringstream s;

    skipComments(file);

    while (true) {
        char c;

        if (!file.get(c).good())
            throw std::runtime_error("PGM file is corrupt");

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            break;
        } else if (c == '#') {
            file.unget();
            skipComments(file);
            break;
        } else if (c < '0' || c > '9') {
            throw std::runtime_error("Invalid token in pgm file at offset " + std::to_string(file.tellg()));
        }
        s << c;
    }

    uint32 value;
    s >> value;
    return value;
}

std::vector<uint08> pgmToLogoBitmap (const char *filename)
{
    std::vector<uint08> raw;

    std::ifstream file(filename, std::ios::binary);
    if (!file.good())
        throw std::runtime_error("Unable to open PGM file: " + std::string(filename));

    char magic[3];
    file.read(magic, 3);
    if (magic[0] != 'P' || magic[1] != '5' ||
            (magic[2] != ' ' && magic[2] != '\t' && magic[2] != '\n' && magic[2] != '\r'))
        throw std::runtime_error("PGM has incorrect header. Only binary PGM files are supported.");

    uint32 width = readUintAscii(file);
    uint32 height = readUintAscii(file);
    uint32 maxval = readUintAscii(file);

    if (width != 100 || height != 17) {
        throw std::runtime_error("PGM has wrong dimensions, 100x17 required\n");
    }

    if (maxval != 255) {
        throw std::runtime_error("PGM has incompatible maxvalue, 255 required\n");
    }

    raw.resize(XBE_UNCOMPRESSED_LOGO_SIZE);
    file.read(reinterpret_cast<char *>(raw.data()), XBE_UNCOMPRESSED_LOGO_SIZE);
    if (file.gcount() != XBE_UNCOMPRESSED_LOGO_SIZE) {
        throw std::runtime_error("PGM file is corrupt\n");
    }

    return raw;
}
