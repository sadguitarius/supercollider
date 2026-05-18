#include "codepoint_stream.hpp"

namespace sc::lex {

CodePointStream::CodePointStream(const char* source, std::size_t source_length, FileCodeLocation source_start_in_file):
    source_start_in_file(source_start_in_file),
    source(source),
    source_length(source_length) {}


[[nodiscard]] FileCodeRange CodePointStream::source_to_file(const SourceCodeRange& source) const {
    return FileCodeRange { source_to_file(source.begin), source_to_file(source.end) };
}

[[nodiscard]] FileCodeLocation CodePointStream::source_to_file(const SourceCodeLocation& source) const {
    return { source.absolute + source_start_in_file.absolute, source.lineNumber + source_start_in_file.lineNumber,
             source.lineNumber == 0 ? source.column + source_start_in_file.column : source.column };
}

[[nodiscard]] std::tuple<SourceCodeLocation, CodePoint> CodePointStream::start_token() {
    return { { state.next_byte_offest, state.current_line_number, state.current_column_count }, advance() };
}

[[nodiscard]] SourceCodeLocation CodePointStream::end_token() const {
    return { state.next_byte_offest, state.current_line_number, state.current_column_count };
}

void CodePointStream::State::update(CodePoint next, std::uint8_t sz) noexcept {
    if (prev_was_newline) {
        current_line_number += 1;
        current_column_count = 0;
        prev_was_newline = false;
    } else {
        // TODO: this is wrong and should be removed.
        current_column_count += 1; // codepoint_width(next);
    }
    prev_was_newline = is_newline(next);
    next_byte_offest += sz;
}

CodePoint CodePointStream::advance() {
    if (state.next_byte_offest >= source_length)
        return 0;

    const auto [c, sz] =
        utf8_sequence_to_codepoint(source + state.next_byte_offest, source_length - state.next_byte_offest);

    state.update(c, sz);

    return c;
}

[[nodiscard]] CodePoint CodePointStream::advance_and_peek() {
    advance();
    return peek();
}

[[nodiscard]] std::tuple<const char*, std::size_t>
CodePointStream::source_code_range_to_text(const SourceCodeRange& range) const {
    return { source + range.begin.absolute, range.end.absolute - range.begin.absolute };
}

void CodePointStream::reset() { state = {}; }

[[nodiscard]] CodePoint CodePointStream::peek() const { return peek_n<1>()[0]; }

}
