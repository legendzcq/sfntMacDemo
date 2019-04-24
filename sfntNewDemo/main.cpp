#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <utility>

#include "include/font.h"
#include "character_predicate.h"
#include "stats.h"
#include "SSubsetter.h"
#include "utils.h"
//
using namespace subtly;

void PrintUsage(const char* program_name) {
    fprintf(stdout, "Usage: %s <input_font_file> <output_font_file>"
            "<start_char> <end_char>\n", program_name);
}

//
//int main(int argc, const char** argv) {
//    const char* program_name = "aaaaaaaa";
////    if (argc < 2) {
//        PrintUsage(program_name);
////        exit(1);
////    }
//
//    const char* input_font_path = "/Users/qishao/Downloads/benmo.ttf";
//    const char* output_font_path = "/Users/qishao/Downloads/benmo_sub.ttf";
//    FontPtr font;
//    font.Attach(subtly::LoadFont(input_font_path));
//
//    int32_t original_size = TotalFontSize(font);
//    Ptr<SSubsetter> subsetter = new SSubsetter(font, NULL);
//    Ptr<Font> new_font;
//    new_font.Attach(subsetter->Subset());
//    if (!new_font) {
//        fprintf(stdout, "Cannot create subset.\n");
//        return 0;
//    }
//
//    subtly::SerializeFont(output_font_path, new_font);
//    subtly::PrintComparison(stdout, font, new_font);
//    int32_t new_size = TotalFontSize(new_font);
//    fprintf(stdout, "Went from %d to %d: %lf%% of original\n",
//            original_size, new_size,
//            static_cast<double>(new_size) / original_size * 100);
//    return 0;
//}









int main() {
    const char* program_name = "dianshijingwei";
    //    if (argc < 5) {
    PrintUsage(program_name);
    //        exit(1);
    //    }

    const char* input_font_path = "/Users/qishao/Downloads/benmo.ttf";
    const char* output_font_path = "/Users/qishao/Downloads/benmo_sub.ttf";
    sfntly::FontPtr font;
    font.Attach(subtly::LoadFont(input_font_path));
    if (font->num_tables() == 0) {
        fprintf(stderr, "Could not load font %s.\n", input_font_path);
        exit(1);
    }

        const char* start_char = "D";
        const char* end_char = "A";
        if (start_char[1] != 0) {
            fprintf(stderr, "Start character %c invalid.\n", start_char[0]);
            exit(1);
        }
        if (end_char[1] != 0) {
            fprintf(stderr, "Start character %c invalid.\n", end_char[0]);
            exit(1);
        }
        int32_t original_size = TotalFontSize(font);


        Ptr<CharacterPredicate> range_predicate =
                new AcceptRange(start_char[0], end_char[0]);
    Ptr<SSubsetter> subsetter = new SSubsetter(font, range_predicate);
        Ptr<Font> new_font;
        new_font.Attach(subsetter->Subset());
        if (!new_font) {
            fprintf(stdout, "Cannot create subset.\n");
            return 0;
        }

        subtly::SerializeFont(output_font_path, new_font);
        subtly::PrintComparison(stdout, font, new_font);
        int32_t new_size = TotalFontSize(new_font);
        fprintf(stdout, "Went from %d to %d: %lf%% of original\n",
                original_size, new_size,
                static_cast<double>(new_size) / original_size * 100);
    return 0;
}



















//
//  main.cpp
//  sfntNewDemo
//
//  Created by 奇少 on 2019/4/23.
//  Copyright © 2019 奇少. All rights reserved.
//

#include "main.hpp"
//
//  main.m
//  sfntNewDemo
//
//  Created by 奇少 on 2019/4/23.
//  Copyright © 2019 奇少. All rights reserved.
//

//#import <Foundation/Foundation.h>
//#include <stdio.h>
//#if _MSC_VER > 12
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#endif
//
//
//#include <vector>
//#include <memory>
//
//#include "font.h"
//#include "memory_byte_array.h"
//#include "memory_output_stream.h"
//#include "type.h"
//#include "tag.h"
//#include "subsetter.h"
//using namespace sfntly;
//
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    NSLog(@"Hello, World!");
//    const char *input_file_path = "/Users/qishao/Downloads/FZZJ-PSBKSJW.TTF";
//    const char *output_file_path ="/Users/qishao/Downloads/benmo_sub.ttf";
//
//
//    UNREFERENCED_PARAMETER(output_file_path);
//    ByteVector input_buffer;
//    FILE* input_file = fopen(input_file_path, "rb");
//    if (input_file == NULL) {
//        fprintf(stderr, "file not found\n");
//        return -1;
//    }
//    fseek(input_file, 0, SEEK_END);
//    size_t file_size = ftell(input_file);
//    fseek(input_file, 0, SEEK_SET);
//    input_buffer.resize(file_size);
//    size_t bytes_read = fread(&(input_buffer[0]), 1, file_size, input_file);
//    UNREFERENCED_PARAMETER(bytes_read);
//    fclose(input_file);
//
//    FontFactoryPtr factory;
//    factory.Attach(FontFactory::GetInstance());
//
//    FontArray font_array;
//    factory->LoadFonts(&input_buffer, &font_array);
//    if (font_array.empty() || font_array[0] == NULL)
//        return -1;
//
//    IntegerList glyphs;
//    for (int32_t i = 10; i < 30; i++) {
//        glyphs.push_back(i);
//    }
//    glyphs.push_back(11);
//    glyphs.push_back(10);
//
//    Ptr<Subsetter> subsetter = new Subsetter(font_array[0], factory);
//    subsetter->SetGlyphs(&glyphs);
//    IntegerSet remove_tables;
//    remove_tables.insert(Tag::DSIG);
//    subsetter->SetRemoveTables(&remove_tables);
//
//    FontBuilderPtr font_builder;
//    font_builder.Attach(subsetter->Subset());
//
//    FontPtr new_font;
//    new_font.Attach(font_builder->Build());
//
//    // TODO(arthurhsu): glyph renumbering/Loca table
//    // TODO(arthurhsu): alter CMaps
//
//    MemoryOutputStream output_stream;
//    factory->SerializeFont(new_font, &output_stream);
//
//    FILE* output_file = fopen(output_file_path, "wb");
//    fwrite(output_stream.Get(), 1, output_stream.Size(), output_file);
//    fflush(output_file);
//    fclose(output_file);
//
//    return 0;
//}
