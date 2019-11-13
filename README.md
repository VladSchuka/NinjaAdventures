# Требования к проекту
---

# Содержание
1 [Введение](#intro)  
1.1 [Назначение](#appointment)  
1.2 [Бизнес-требования](#business_requirements)  
1.2.1 [Возможности бизнеса](#business_opportunities)  
2 [Требования пользователя](#user_requirements)  
2.1 [Программные интерфейсы](#software_interfaces)  
2.2 [Интерфейс пользователя](#user_interface)  
2.3 [Характеристики пользователей](#user_specifications)  
2.4 [Предположения и зависимости](#assumptions_and_dependencies)  
3 [Системные требования](#system_requirements)  
3.1 [Функциональные требования](#functional_requirements)  
3.2 [Нефункциональные требования](#non-functional_requirements)  
3.2.1 [Атрибуты качества](#quality_attributes)  
3.2.2 [Требования к безопасности](#security_requirements)  

<a name="intro"/>

# 1 Введение

Тип приложения: мультиплеерный 2D-платформер.
Название продукта: "Ninja Adventures"

<a name="appointment"/>

## 1.1 Назначение
Простая игра для 2 и более игроков. Продукт должен обеспечивать:  
1) Стабильное соединение между клиентами,Клиентами и сервером.  
<a name="business_requirements"/>

## 1.2 Бизнес-требования

<a name="business_opportunities"/>

### 1.2.1 Исходные данные
Разработка игры позволит получить необходимый опыт и финансы для дальнейшего существования.

<a name="user_requirements"/>

# 2 Требования пользователя

<a name="software_interfaces"/>

## 2.1 Программные интерфейсы

1. Графический интерфейс должен обеспечиваться графической библиотекой OpenGL.
2. Соединение между клиентами и сервером осуществляться с помощью встроенной в Windows библиотекой <Winsock.H>.

<a name="user_interface"/>

## 2.2 Интерфейс пользователя
 
![Главное окно программы](https://github.com/VladSchuka/NinjaAdventures/blob/master/Images/Capture2.PNG)  
Рисунок 1. Главное окно программы

Главное окно игры должно выводить на экран уровень, представленный блоками, и модели игроков. Базовый Размер окна - 800х600  

<a name="user_specifications"/>

## 2.3 Характеристики пользователей
Пользователи продукта подразделяются на:  
1. Игроки, которые создают сервер на своем компьютере.
2. Игроки, которые подключаются к серверу. 
Указанные пользователи составляют один класс: обычные пользователи, которые в состоянии работать с интуитивно-понятной, лёгкой для освоения системой.

<a name="assumptions_and_dependencies"/>

## 2.4 Предположения и зависимости
1. Разрешение экрана пользователя продукта – любое.  
2. Для лучшего восприятия отображаемой информации размер окна должен быть изменяемым пользователем, чтобы подходит большинству систем.

<a name="system_requirements"/>

# 3 Системные требования
Информационная автоматизированная система может работать под управлением семейства операционных систем Win32 (Windows 95, Windows 98, Windows 2000, Windows NT и т.д.) и с любым процессором года выпуска 2014 и выше.

<a name="functional_requirements"/>

## 3.1 Функциональные требования
1. Возможность свободно подключатся к существующей игре по локальной сети. 
2. Возможность создавать сервер.
3. Управление персонажем через WASD, Space для атаки, R для дальней атаки, Enter для написания сообщения в чат. 

<a name="non-functional_requirements"/>

## 3.2 Нефункциональные требования

<a name="quality_attributes"/>

### 3.2.1 АТРИБУТЫ КАЧЕСТВА
Атрибуты, важные для пользователей:  
1.Доступность. Система должна быть доступна на большинстве современных машин. 

2.Удобство и простота использования. После подключения к игре, пользователь может начать играть при помощи клавиш "WASD" для перемещения, "SPACE" и "R" для атаки.  
Атрибуты, важные для разработчиков:  
1. Лёгкость в эксплуатации. Вложенность вызываемых функций не должна превышать 10 уровней.  
