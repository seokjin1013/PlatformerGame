template <typename T>
void Object::move_box_collision(Vec2<double>& velocity) {
    auto pool = room->get_pool();
    double min_collision_point = 1;
    int collision_direction = -1;
    for (const auto e : pool) {
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(velocity, e)) {
                int dir = get_box_collision_direction(velocity, e);
                double point = get_box_collision_velocity_multiplier(velocity, e, dir);
                if (min_collision_point > point) {
                    min_collision_point = point;
                    collision_direction = dir;
                }
            }
        }
    }
    pos += velocity * min_collision_point;
    if (min_collision_point < 1) {
        if (collision_direction & 1)
            velocity.y = 0;
        else
            velocity.x = 0;
        move_box_collision<T>(velocity);
    }
}

template <typename T>
bool Object::check_box_collision(const Vec2<double>& velocity) {
    auto pool = room->get_pool();
    for (const auto e : pool) {
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(velocity, e)) {
                return true;
            }
        }
    }
    return false;
}