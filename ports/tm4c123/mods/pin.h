/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2018 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MICROPY_INCLUDED_TM4C_MODS_PINS_H_
#define MICROPY_INCLUDED_TM4C_MODS_PINS_H_

#include <stdint.h>

#include "py/runtime.h"
#include "py/gc.h"
#include "py/qstr.h"

//#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_hibernate.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/interrupt.h"
#include "hal_pins.h"



typedef struct {
  qstr name;
  int8_t  idx;
  uint8_t fn;
  uint8_t unit;
  uint8_t type;
  void* reg;
} pin_af_obj_t;

typedef struct {
    const mp_obj_base_t base;
    const qstr          name;
    const uint32_t      port;   //Address of Port
    const periph_gpio_t gpio;   //Structure for register access
    const pin_af_obj_t  *af_list;
    uint32_t            dir;
    uint32_t            type;
    uint32_t            drive;
    const uint8_t       pin_mask;
    const uint8_t       pin_num;
    int8_t              af;
    const uint8_t       num_afs;     // 255 AFs
    uint8_t             value;
    uint8_t             used;
    uint32_t            irq_trigger;
    uint32_t            irq_flags;
} pin_obj_t;

extern const mp_obj_type_t pin_type;
extern const mp_obj_type_t pin_af_type;

#include "genhdr/pins.h"

extern const pin_named_pin_t pin_board_pins[];
extern const pin_named_pin_t pin_cpu_pins[];


typedef struct {
    const char *name;
    const pin_obj_t *pin;
} pin_named_pin_t;

typedef struct {
    mp_obj_base_t base;
    qstr name;
    const pin_named_pin_t *named_pins;
} pin_named_pins_obj_t;

extern const mp_obj_type_t pin_board_pins_obj_type;
extern const mp_obj_dict_t pin_board_pins_locals_dict;
extern const mp_obj_type_t pin_cpu_pins_obj_type;
extern const mp_obj_dict_t pin_cpu_pins_locals_dict;

MP_DECLARE_CONST_FUN_OBJ_KW(pin_init_obj);

void pin_init0(void);

const pin_obj_t *pin_find(mp_obj_t user_obj);
const pin_obj_t *pin_find_named_pin(const mp_obj_dict_t *named_pins, mp_obj_t name);
const pin_af_obj_t *pin_find_af(const pin_obj_t *pin, uint8_t fn, uint8_t unit);
const pin_af_obj_t *pin_find_af_by_index(const pin_obj_t *pin, mp_uint_t af_idx);
const pin_af_obj_t *pin_find_af_by_name(const pin_obj_t *pin, const char *name);

#endif // MICROPY_INCLUDED_TM4C_MODS_PINS_H_
