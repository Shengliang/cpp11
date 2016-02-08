

// unique_ptr constructor example
#include <iostream>
#include <memory>
#include <cassert>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

class MemBlock {
 void *addr_ = nullptr;
 size_t size_ = 0;
 int wptr_ = 0;
 int rptr_ = 0;
 int pagesize_ = 0;
 int pagenum_ = 0;
 public:
  MemBlock(void * addr, size_t size): addr_(addr), size_(size) {
  }
  MemBlock(size_t pagenum) {
    pagesize_ = sysconf(_SC_PAGESIZE);
    pagenum_ = pagenum;
    size_ = pagenum_ * pagesize_;
    addr_ = mmap(NULL, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    std::cout << __FUNCTION__ << std::endl;
    print();
  }

  ~MemBlock() {
    munmap(addr_, size_);
    std::cout << __FUNCTION__ << std::endl;
    print();
  }
  void print() {
    std::cout << "addr_:" << std::hex << reinterpret_cast<uint64_t>(addr_) << std::endl;
    std::cout << "size_:" << std::hex << size_ << std::endl;
  }
  void dump(void * buf, size_t size) {
    int * p = reinterpret_cast<int *>(buf);
    std::cout << "---------------------" << std::endl;
    std::cout << "addr:" << std::hex << reinterpret_cast<uint64_t>(buf) << std::endl;
    std::cout << "size:" << std::hex << size << std::endl;
    for(int i = 0; i < size/sizeof(int); i++) {
      if ((i%8) == 0) {
        std::cout << std::endl;
      }
      char buffer[32];
      sprintf(buffer, "0x%08X ", p[i]);
      std::cout << buffer;
    }
    std::cout << std::endl;
  }
  void write(const char * data, size_t n) {
       char * p = reinterpret_cast<char *>(addr_);
       p += wptr_;
       for(int i = 0; i < n; i++) {
         p[i] = data[i];
       }
  }
  void read(char * data, size_t n) {
       char * p = reinterpret_cast<char *>(addr_);
       p += rptr_;
       for(int i = 0; i < n; i++) {
         data[i] = p[i];
       }
  }
  void fill(char * buf, size_t n) {
    int * p = reinterpret_cast<int *>(buf);
    for(int i = 0; i < n/sizeof(int); i++) {
      p[i] = i;
    }
  }
  int compare(char *buf1, char *buf2, size_t n) {
    int counter = 0;
    int * p1 = reinterpret_cast<int *>(buf1);
    int * p2 = reinterpret_cast<int *>(buf2);
    for(int i = 0; i< n/sizeof(int); i++) {
         if (p1[i] != p2[i]) {
           counter++;
         }
    }
    if (counter == 0) {
      std::cout << "Pass" << std::endl;
    }
    else {
      std::cout << "Fail:" << counter << std::endl;
    }
    return counter;
  }
  int selftest(void) {
    char write_buffer[size_];
    char read_buffer[size_];
    fill(write_buffer, sizeof(write_buffer));
    dump(write_buffer, 16);
    dump(&write_buffer[size_-16], 16);
    write(write_buffer, sizeof(write_buffer));
    read(read_buffer, sizeof(read_buffer));
    dump(read_buffer, 16);
    dump(&read_buffer[size_-16], 16);
    // dump(&read_buffer, sizeof(read_buffer));
    return compare(read_buffer, write_buffer, size_);
  }
};

int main () {
  MemBlock block(4);
  std::cout << block.selftest();

  std::unique_ptr<MemBlock> pMem(new MemBlock(4));
  std::cout << pMem->selftest();

  std::default_delete<int> d;
  std::unique_ptr<int> u1;
  std::unique_ptr<int> u2 (nullptr);
  std::unique_ptr<int> u3 (new int, std::default_delete<int>());
  std::cout << "u3: " << (u3?"not null":"null") << '\n';
  std::unique_ptr<int> u4 (std::move(u3));
  std::cout << "u3: " << (u3?"not null":"null") << '\n';
  std::cout << "u4: " << (u4?"not null":"null") << '\n';

  std::unique_ptr<int> u5 (new int);
  std::unique_ptr<int> u6 (new int, d);
  std::unique_ptr<int> u7 (std::move(u4));
  std::unique_ptr<int> u8 (std::auto_ptr<int>(new int));

  std::cout << "u1: " << (u1?"not null":"null") << '\n';
  std::cout << "u2: " << (u2?"not null":"null") << '\n';
  std::cout << "u3: " << (u3?"not null":"null") << '\n';
  std::cout << "u4: " << (u4?"not null":"null") << '\n';
  std::cout << "u5: " << (u5?"not null":"null") << '\n';
  std::cout << "u6: " << (u6?"not null":"null") << '\n';
  std::cout << "u7: " << (u7?"not null":"null") << '\n';
  std::cout << "u8: " << (u8?"not null":"null") << '\n';

  return 0;
}
