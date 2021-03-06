//
// Created by Joseph Montanez on 4/8/18.
//

#ifndef PHP_RAYLIB_CAMERA3D_H
#define PHP_RAYLIB_CAMERA3D_H

extern zend_class_entry *php_raylib_camera3d_ce;

typedef struct _php_raylib_camera3d_object {
    Camera3D camera3d;
    zend_object std;
} php_raylib_camera3d_object;

static inline php_raylib_camera3d_object *php_raylib_camera3d_fetch_object(zend_object *obj) {
    return (php_raylib_camera3d_object *)((char *)obj - XtOffsetOf(php_raylib_camera3d_object, std));
}

void php_raylib_camera3d_free_storage(zend_object *object TSRMLS_DC);
zend_object * php_raylib_camera3d_new(zend_class_entry *ce TSRMLS_DC);

#define Z_CAMERA3D_OBJ_P(zv) php_raylib_camera3d_fetch_object(Z_OBJ_P(zv));

void php_raylib_camera3d_startup(INIT_FUNC_ARGS);

#endif //PHP_RAYLIB_CAMERA3D_H
