#ifndef _VIEW_H_
#define _VIEW_H_

class Board;
class Builder;

class View {
    View();
  public:
    static View *getInstance();
    static void invalidInput();
    static void invalidCommand();
    static void cannotBuildHere();
    static void doNotHaveEnoughResources();
    View(const View &other) = delete;
    View& operator=(const View &other) = delete;
    void printBoard(Board *board);
    void printBuilder(Builder *builder);
    void printResidences(Builder *builder);
};

#endif
