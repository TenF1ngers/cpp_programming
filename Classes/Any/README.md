### Any (Выполнены все задания)

*В этом задании необходимо реализовать упрощенный аналог класса `std::any` с помощью механизма "type erasure" (стирание
типов).*

#### std::any (C++17)
В C++17 появился класс, позволяющий хранить в себе объекты произвольных типов. Ровно как в динамически типизированных
языках, типа Python, одна и та же переменная может использоваться для хранения разных типов (`a = "aba"; a = 3;` -
валидный код), при этом формально, конечно, ее тип всегда будет оставаться `std::any`.

*Пример:*

```c++
std::any a = std::string("aba");  // сейчас a содержит строку "aba"

a = true;  // а теперь булевское значение true

std::any b;  // "пустой" объект
```

Но C++ - статически типизированный язык, поэтому "за удовольствие приходится платить". Во-первых, дополнительными
накладными расходами, а, во-вторых, удобством использования. Например, нельзя просто так взять и присвоить значение
`std::any` другой переменной, даже если тип ее текущего значения совпадает с типом принимающей стороны (подумайте,
почему, в чем сложность реализации такого механизма?). Для получения значения конкретного типа необходимо явно попросить
об этом с помощью шаблонной функции `std::any_cast<T>`, где `T` - требуемый тип. В случае, если в данный момент объект
содержит не тип `T`, бросается исключение `std::bad_any_cast`.

*Пример:*
```c++
std::any a = std::string("aba");  // сейчас a содержит строку "aba"
    
auto str = std::any_cast<std::string>(a);  // корректно получено текущее значение   
 
auto x = std::any_cast<int>(a);  // выбросится исключение, так как a содержит не int
```

Полезные методы:
* `reset()` - обнуляет объект, делая его пустым;
* `swap(std::any&)` - обменивает содержимое;
* `has_value()` - `true`, если объект не пуст, `false` иначе;
* Внешняя шаблонная функция `std::make_any<T>(args...)` - принимает аргументы конструктора, с которым
  нужно создать объект типа `T` и возвращает `std::any` с этим объектом.

Подробнее [в справочнике](https://en.cppreference.com/w/cpp/utility/any).

#### Type erasure

Возникает естественный вопрос, как реализовать подобный механизм? Что нужно хранить в полях класса, чтобы иметь
возможность сохранять объекты любых типов и в нужный момент понимать, что за тип хранится в нем?

Относительно простое решение - хранить указатель `void*` на динамическую память. При присваивании выделять в куче память
под новый объект, освобождать при изменении типа объекта. Значение типа получать, например, с помощью оператора
`typeid`. Но здесь возникают серьезные вопросы по безопасности работы с "сырой" памятью и приведением типов между
указателями.

В этом задании мы предлагаем познакомиться с более изящной техникой "стирания типов"
([type erasure](http://www.lucadavidian.com/2019/08/26/type-erasure-in-c/)). Окей, мы не можем хранить в поле класса
произвольный тип, он должен быть фиксирован для всех объектов. Что бы нам такое сохранить, чтобы тип был фиксирован, но
фактически под ним могло лежать значение другого типа? Стоп, но это же ровно то, что достигается при помощи
динамического полиморфизма (указатель на полиморфный базовый класс может указывать на любого из наследников). Таким
образом, если создать полиморфный базовый класс `Base`, от которого затем унаследовать всевозможные типы (что?!), то
можно будет хранить в поле указатель на базу. Но как унаследовать, например, `int` или `std::string` от `Base`? Спойлер:
никак. Но можно написать специальные классы-обертки над типами: `DerivedInt`, `DerivedString`, `DerivedBool`... и
наследовать их... Стоп. C++ же нам позволяет автоматически генерировать классы параметризованные произвольными типами,
используя механизм шаблонов! Достаточно написать реализацию для `Derived<T>` и нужные версии будут создаваться
автоматически по мере необходимости!

#### Детали реализации

Для решения вам понадобится написать пустой (без полей) абстрактный базовый класс `IHolder` (`Base`) и шаблонный класс
`AnyHolder<T>` (`Derived`) -- наследник `IHolder`, который будет хранить в себе единственное поле типа `T` - требуемое
значение.  В свою очередь, `AnyHolder` должен поддерживать конструктор от `T`, чтобы инициализировать поле (будем
считать, что у `T` есть конструктор копирования и/или move конструктор).

Основной класс `Any` должен иметь:
* Поле-указатель (умный) на `IHolder`.
* Конструктор по умолчанию, выставляющий указатель в `nullptr` (пустой объект)
* Конструктор копирования. Для удобства реализации, заведите в `IHolder` чисто виртуальный метод `Clone()`,
  который возвращает указатель на новый выделенный объект. Естественно, нужно будет написать его
  реализацию в `AnyHolder`. Все копирование в итоге должно свестись к одному вызову `Clone()`.
* Шаблонный конструктор от объекта произвольного типа `T` (который должен хранить объект `Any`). Здесь
  нужно создать в куче объект `AnyHolder<T>` и присвоить его адрес полю-указателю на `IHolder`. (Обращаем внимание,
  что здесь-то и произошло "стирание типа")
* Аналогичный оператор присваивания.
* Методы `Swap(Any& other)`, `Reset()` и `HasValue()` (описания даны выше).

Также реализуйте класс исключения `BadAnyCast`, и внешнюю шаблонную функцию
`template <class T> T any_cast(const Any& value)`, которая возвращает значение, в случае, если `IHolder` указывает на
`AnyHolder<T>` и бросает `BadAnyCast` в противном случае (вам наверняка пригодится `dynamic_cast`).

**Замечания.**

1. Класс активно работает с кучей и механизмом позднего связывания, что может существенно влиять на производительность,
   поэтому его стоит использовать с осторожностью.

2. Решение должно состоять из одного файла `any.h`.