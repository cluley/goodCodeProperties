#pragma once

#include <fstream>
#include <iostream>

class Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    virtual ~Printable() = default;

    virtual std::string print() const = 0;
    virtual Format getFormat() const = 0;
};

class PrintAsHTML : public Printable {
public:
    PrintAsHTML(std::string data) : data_(std::move(data)) {}

    std::string print() const { return "<html>" + data_ + "<html/>"; }
    Format getFormat() const override { return format_; }
private:
    std::string data_;
    Format format_ = Format::kHTML;
};

class PrintAsText : public Printable {
public:
    PrintAsText(std::string data) : data_(std::move(data)) {}

    std::string print() const { return data_; }
    Format getFormat() const override { return format_; }
private:
    std::string data_;
    Format format_ = Format::kText;
};

class PrintAsJSON : public Printable {
public:
    PrintAsJSON(std::string data) : data_(std::move(data)) {}

    std::string print() const { return "{ \"data\": \"" + data_ + "\"}"; }
    Format getFormat() const override { return format_; }
private:
    std::string data_;
    Format format_ = Format::kJSON;
};

class proxy {
private:
    std::ofstream file_;
    const Printable* printable_;
public:
    proxy(std::ofstream& file, const Printable* printable)
        : file_(std::move(file)), printable_(printable) {}

    void asHTML() {
        checkAndPrint(Printable::Format::kHTML);
    }
    void asText() {
        checkAndPrint(Printable::Format::kText);
    }
    void asJSON() {
        checkAndPrint(Printable::Format::kJSON);
    }
private:
    void checkAndPrint(Printable::Format format) {
        if (printable_->getFormat() != format)
            throw std::runtime_error("Invalid format!");
        else
            file_ << printable_->print();
    }
};

proxy saveTo(std::ofstream& file, const Printable* printable)
{
    return proxy(file, printable);
}