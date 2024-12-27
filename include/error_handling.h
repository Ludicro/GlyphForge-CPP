#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdexcept>
#include <string>

class GlyphForgeError : public std::runtime_error {
public:
    explicit GlyphForgeError(const std::string& message) 
        : std::runtime_error(message) {}
};

class FileError : public GlyphForgeError {
public:
    explicit FileError(const std::string& filename) 
        : GlyphForgeError("File error: " + filename) {}
};

class PatternError : public GlyphForgeError {
public:
    explicit PatternError(const std::string& message) 
        : GlyphForgeError("Pattern error: " + message) {}
};

class RenderError : public GlyphForgeError {
public:
    explicit RenderError(const std::string& message) 
        : GlyphForgeError("Render error: " + message) {}
};

#endif // ERROR_HANDLING_H
