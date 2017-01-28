//
// Created by abijosh on 10/17/16.
//

#ifndef ICATGAME_AABB2D_H
#define ICATGAME_AABB2D_H


class BB2D {
public:
    BB2D(glm::vec2 leftBottom, glm::vec2 rightTop);
    ~BB2D();

private:
    glm::vec2 leftBottom, rightTop;
};


#endif //SKATEBALL_AABB2D_H
