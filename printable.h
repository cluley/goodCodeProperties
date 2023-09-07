#pragma once

#include <fstream>
#include <iostream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string print() const = 0;
};

class DataHTML : public Printable {
public:
    DataHTML(std::string data) : data_(std::move(data)) {}

    std::string print() const override { 
        return "<html>" + data_ + "<html/>"; 
    }
private:
    std::string data_;
};

class DataText : public Printable {
public:
    DataText(std::string data) : data_(std::move(data)) {}

    std::string print() const override { 
        return data_; 
    }
private:
    std::string data_;
};

class DataJSON : public Printable {
public:
    DataJSON(std::string data) : data_(std::move(data)) {}

    std::string print() const override { 
        return "{ \"data\": \"" + data_ + "\"}"; 
    }
private:
    std::string data_;
};

void saveTo(std::ofstream& file, const Printable& printable)
{
    file << printable.print();
}