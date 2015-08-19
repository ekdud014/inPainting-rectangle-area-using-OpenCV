g++ -I./include src/inpaint_main.cc src/inpaint.cc -DINPAINTING -o inpaint `pkg-config opencv --cflags --libs`
