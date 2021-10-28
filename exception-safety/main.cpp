#include <iostream>
#include <stdexcept>
#include <string>
#include <new>

struct IThrow {
    IThrow() {
        throw std::runtime_error( std::string(__PRETTY_FUNCTION__) );
    }
};

class Stuff {
public:
    Stuff() 
    try :
             m_i1( new(std::nothrow) int(5) ),
             m_i2( new(std::nothrow) int(2) ),
        m_ithrow( new(std::nothrow) IThrow )
        {
            std::cout<<__PRETTY_FUNCTION__<<std::endl;
            if( not m_i1 or not m_i2 or not m_ithrow )
            {
                std::cout<<__PRETTY_FUNCTION__<<" throw ptr addr: "<< std::size_t(m_ithrow) <<std::endl;
            }
        }
    catch( const std::runtime_error& e ) {
        std::cout<<"handled in the ctor: "<<e.what()<<std::endl;

        if( m_i1 ) {
            std::cout<<__PRETTY_FUNCTION__<<": cleaning up m_i1"<<std::endl;
            delete m_i1;
        }

        if( m_i2 ) {
            std::cout<<__PRETTY_FUNCTION__<<": cleaning up m_i2"<<std::endl;
            delete m_i2;
        }

        if( m_ithrow ) {
            std::cout<<__PRETTY_FUNCTION__<<": cleaning up m_ithrow"<<std::endl;
            delete m_ithrow;
        }

        throw; // re-throw
    }

    ~Stuff() {
        std::cout<<__PRETTY_FUNCTION__<<std::endl;
        delete m_i1;
        delete m_i2;
        delete m_ithrow;
    }

private:
    int*        m_i1 = nullptr;
    int*        m_i2 = nullptr;
    IThrow* m_ithrow = nullptr;
};

struct Stuff2 {

    Stuff2() {
        std::cout<<__PRETTY_FUNCTION__<<std::endl;
        try {
            m_i1 = new(std::nothrow) int(5);
            m_i2 = new(std::nothrow) int(2);
            m_ithrow = new(std::nothrow) IThrow;
        } catch( const std::runtime_error& e ) {
            std::cout<<"handled in the ctor: "<<e.what()<<std::endl;
            if( m_i1 ) {
                std::cout<<__PRETTY_FUNCTION__<<": cleaning up m_i1"<<std::endl;
                delete m_i1;
            } else {
                std::cout<<__PRETTY_FUNCTION__<<": no need to clean up m_i1"<<std::endl;
            }

            if( m_i2 ) {
                std::cout<<__PRETTY_FUNCTION__<<": cleaning up m_i2"<<std::endl;
                delete m_i2;
            } else {
                std::cout<<__PRETTY_FUNCTION__<<": no need to clean up m_i2"<<std::endl;
            }

            if( m_ithrow ) {
                std::cout<<__PRETTY_FUNCTION__<<": cleaning up m_ithrow"<<std::endl;
                delete m_ithrow;
            } else {
                std::cout<<__PRETTY_FUNCTION__<<": no need to clean up m_ithrow"<<std::endl;
            }
            throw; // re-throw
        }
    }

    ~Stuff2() {
        std::cout<<__PRETTY_FUNCTION__<<std::endl;
        delete m_i1;
        delete m_i2;
        delete m_ithrow;
    }

    void f() const& {}
private:
    int*        m_i1 = nullptr;
    int*        m_i2 = nullptr;
    IThrow* m_ithrow = nullptr;
};

int main() {
    std::cout<<"Hello, world!"<<std::endl;

    try {
        Stuff2 s2;
        s2.f();
    } catch( ... ) {
        std::cout<<__PRETTY_FUNCTION__<<", Stuff2"<<std::endl;
    }

    try { Stuff s; }
    catch( ... ) {
        std::cout<<__PRETTY_FUNCTION__<<", Stuff"<<std::endl;
    }

    return 0;
}
