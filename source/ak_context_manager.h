/* ----------------------------------------------------------------------------------------------- */
/*  Copyright (c) 2017 by Axel Kenzo, axelkenzo@mail.ru                                            */
/*                                                                                                 */
/*  Разрешается повторное распространение и использование как в виде исходного кода, так и         */
/*  в двоичной форме, с изменениями или без, при соблюдении следующих условий:                     */
/*                                                                                                 */
/*   1. При повторном распространении исходного кода должно оставаться указанное выше уведомление  */
/*      об авторском праве, этот список условий и последующий отказ от гарантий.                   */
/*   2. При повторном распространении двоичного кода должна сохраняться указанная выше информация  */
/*      об авторском праве, этот список условий и последующий отказ от гарантий в документации     */
/*      и/или в других материалах, поставляемых при распространении.                               */
/*   3. Ни имя владельца авторских прав, ни имена его соратников не могут быть использованы в      */
/*      качестве рекламы или средства продвижения продуктов, основанных на этом ПО без             */
/*      предварительного письменного разрешения.                                                   */
/*                                                                                                 */
/*  ЭТА ПРОГРАММА ПРЕДОСТАВЛЕНА ВЛАДЕЛЬЦАМИ АВТОРСКИХ ПРАВ И/ИЛИ ДРУГИМИ СТОРОНАМИ "КАК ОНА ЕСТЬ"  */
/*  БЕЗ КАКОГО-ЛИБО ВИДА ГАРАНТИЙ, ВЫРАЖЕННЫХ ЯВНО ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ             */
/*  ОГРАНИЧИВАЯСЬ ИМИ, ПОДРАЗУМЕВАЕМЫЕ ГАРАНТИИ КОММЕРЧЕСКОЙ ЦЕННОСТИ И ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ */
/*  ЦЕЛИ. НИ В КОЕМ СЛУЧАЕ НИ ОДИН ВЛАДЕЛЕЦ АВТОРСКИХ ПРАВ И НИ ОДНО ДРУГОЕ ЛИЦО, КОТОРОЕ МОЖЕТ    */
/*  ИЗМЕНЯТЬ И/ИЛИ ПОВТОРНО РАСПРОСТРАНЯТЬ ПРОГРАММУ, КАК БЫЛО СКАЗАНО ВЫШЕ, НЕ НЕСЁТ              */
/*  ОТВЕТСТВЕННОСТИ, ВКЛЮЧАЯ ЛЮБЫЕ ОБЩИЕ, СЛУЧАЙНЫЕ, СПЕЦИАЛЬНЫЕ ИЛИ ПОСЛЕДОВАВШИЕ УБЫТКИ,         */
/*  ВСЛЕДСТВИЕ ИСПОЛЬЗОВАНИЯ ИЛИ НЕВОЗМОЖНОСТИ ИСПОЛЬЗОВАНИЯ ПРОГРАММЫ (ВКЛЮЧАЯ, НО НЕ             */
/*  ОГРАНИЧИВАЯСЬ ПОТЕРЕЙ ДАННЫХ, ИЛИ ДАННЫМИ, СТАВШИМИ НЕПРАВИЛЬНЫМИ, ИЛИ ПОТЕРЯМИ ПРИНЕСЕННЫМИ   */
/*  ИЗ-ЗА ВАС ИЛИ ТРЕТЬИХ ЛИЦ, ИЛИ ОТКАЗОМ ПРОГРАММЫ РАБОТАТЬ СОВМЕСТНО С ДРУГИМИ ПРОГРАММАМИ),    */
/*  ДАЖЕ ЕСЛИ ТАКОЙ ВЛАДЕЛЕЦ ИЛИ ДРУГОЕ ЛИЦО БЫЛИ ИЗВЕЩЕНЫ О ВОЗМОЖНОСТИ ТАКИХ УБЫТКОВ.            */
/*                                                                                                 */
/*   ak_context_manager.h                                                                          */
/* ----------------------------------------------------------------------------------------------- */
#ifndef __AK_CONTEXT_MANAGER_H__
#define __AK_CONTEXT_MANAGER_H__

/* ----------------------------------------------------------------------------------------------- */
 #include <libakrypt.h>

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс состояний ключевого контекста */
 typedef enum {
  /*! \brief контект не определен */
   node_undefined,
  /*! \brief контекст совпадает с хранимым вариантом (только создан/считан/записан) */
   node_is_equal,
  /*! \brief контекст изменен в процессе работы */
   node_modified
} ak_context_node_status;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Элемент структуры, предназначенной для управления ключевыми контекстами */
 struct context_node {
  /*! \brief дескриптор ключа */
   ak_key id;
  /*! \brief указатель на ключ */
   ak_pointer keyctx;
  /*! \brief тип ключа */
   ak_oid_engine engine;
  /*! \brief пользовательское описание */
   ak_buffer description;
  /*! \brief статус ключа */
   ak_context_node_status status;
  /*! \brief функция удаления и очистки памяти из под ключа */
   ak_function_free_object *free;
};

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Указатель на элемент структуры управления ключами */
 typedef struct context_node *ak_context_node;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Структура, предназначенная для управления контекстами */
/*! Структура реализует массив указателей на произвольные контексты библиотеки, для которых
    определена функция освобождения памяти _destroy(). Данный массив предназначен, в первую очередь,
    для хранения указателей на ключевые контексты. Однако библиотекой в массив могут помещаться
    контексты, создаваемые динамически в ходе работы, например,
    - буффер, содержащий узлы замены алгоритма блочного шифрования ГОСТ 28147-89,
    - буффер с параметрами эллиптической кривой,
    - структура, используемая для вычисления сжимающего отображения и т.п.

    При инициализации библиотеки создается один объект данного типа, который используется
    для работы с ключами пользователя.
    Доступ пользователям библиотеки к данной структуре хранения данных закрыт.                     */
/* ----------------------------------------------------------------------------------------------- */
 struct context_manager {
  /*! \brief массив указателей на структуры управления ключевыми контекстами */
   ak_context_node *array;
  /*! \brief общее количество выделенной по структуры управления памяти */
   size_t size;
  /*! \brief текущее количество структур управления */
   size_t count;
  /*! \brief генератор, используемый для выработки новыйх ключей */
   ak_random generator;
  /*! \brief маска доступа к номеру структуры управления */
   ak_uint64 imask;
};

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Указатель на структуру управления ключами */
 typedef struct context_manager *ak_context_manager;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация структуры управления ключами */
 int ak_context_manager_create( ak_context_manager , ak_random );
/*! \brief Уничтожение структуры управления ключами */
 int ak_context_manager_destroy( ak_context_manager );

#endif
/* ----------------------------------------------------------------------------------------------- */
/*                                                                           ak_context_manager.h  */
/* ----------------------------------------------------------------------------------------------- */