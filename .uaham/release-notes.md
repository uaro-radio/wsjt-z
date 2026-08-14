## Що це

Збірка **WSJT-Z** з інтеграцією [uahamaward.com](https://uahamaward.com). Усе інше — оригінальний WSJT-Z від SQ9FVE, без змін.

Це **не офіційний реліз WSJT-Z**. Про проблеми саме з тим, що описано нижче, пишіть сюди, а не авторам WSJT-Z чи WSJT-X.

## Що змінилось від `uaham1`

Нічого з того, що ви побачите під час роботи: **функціонально ця збірка така сама**, і якщо `uaham1` у вас працює, оновлюватись не обов'язково.

Змінилось усередині. Попередня збірка проходила лише тому, що для `map65` і `qmap` — двох успадкованих програм, яких ця збірка не торкається — довелося вимкнути суворий режим компілятора. Тепер там перенесене справжнє виправлення з WSJT-X, а суворий режим повернуто для всього дерева. Дорогою це закрило кілька місць у переліку звукових пристроїв `map65`, де довга назва пристрою писалась у буфер без обмеження довжини.

## Що додано

**Фільтр країн (Налаштування → UaHam Filter).** Обирайте країни зі списку DXCC у двох режимах: *ховати обрані* або *показувати лише обрані*. Прихована станція не з'являється ні у вікні активності діапазону, ні у вікні частоти прийому, ні в переліку активних станцій — і автопослідовність не відповість їй навіть на прямий виклик. `ALL.TXT` зберігає всі декоди, а програми, що читають WSJT-Z по UDP (JTAlert, GridTracker), бачать усе, доки ви самі не увімкнете фільтрування UDP.

На відміну від наявних фільтрів, які шукають збіг тексту в повідомленні, цей питає `cty.dat` — тому «лише Японія» працює для всіх префіксів JA, JE–JS, 7J–7N, 8J–8N разом, включно зі складеними позивними.

**Пряме з'єднання з сайтом (Налаштування → UaHam Site).** WSJT-Z сам віддає кожен записаний зв'язок сторінкам нагород на uahamaward.com — байдуже, записали ви його вручну чи це зробила автопослідовність. **Окрема програма-місток більше не потрібна:** нічого не треба завантажувати й нічого оновлювати. Якщо жодну сторінку журналу не відкрито, нічого не надсилається, і запис зв'язку працює точно так, як завжди.

**Український інтерфейс (Налаштування → Language).** Перекладено головне вікно, меню, налаштування, запис QSO та вікна помилок. Назви режимів, діапазонів, одиниці та ефірні скорочення лишилися англійською навмисно. Мова діє з наступного запуску.

**Вкладка «UaHam» у головному вікні** показує режим фільтра, скільки декодів приховано, чи підключений браузер і скільки QSO надіслано. Те саме коротко — в рядку стану.

## Виправлено в успадкованому коді

Прапорець фільтрації скидався один раз на пачку декодів замість кожного декоду. Через це варто було відфільтрувати один сигнал у періоді — і зникали всі наступні в тій самій пачці, разом з автовідповіддю.

## Встановлення

Windows — `.exe`. Linux — `.deb` або `.rpm` під вашу архітектуру.

---

# English

## What this is

A build of **WSJT-Z** with [uahamaward.com](https://uahamaward.com) integration. Everything else is SQ9FVE's WSJT-Z, unchanged.

This is **not an official WSJT-Z release**. Report problems with what is described below here, not to the WSJT-Z or WSJT-X authors.

## Changed since `uaham1`

Nothing you will see while operating: **this build is functionally identical**, and if `uaham1` works for you there is no need to update.

What changed is underneath. The previous build only compiled because strict compiler checks had been switched off for `map65` and `qmap` — two inherited applications this build does not touch. They now carry the real fix from upstream WSJT-X, and strict checking is back across the whole tree. On the way it closed several places in `map65`'s sound-device listing where a long device name was written into a buffer without a length limit.

## What was added

**Country filter (Settings → UaHam Filter).** Pick DXCC entities from a list, in two modes: *hide the chosen ones* or *show only those*. A hidden station appears in neither Band Activity, nor Rx Frequency, nor Active Stations — and auto-sequencing will not answer it even when it calls you directly. `ALL.TXT` keeps every decode, and programs reading WSJT-Z over UDP (JTAlert, GridTracker) see everything, unless you switch on UDP filtering yourself.

Unlike the existing filters, which look for text inside the message, this one asks `cty.dat` — so "Japan only" covers JA, JE–JS, 7J–7N and 8J–8N together, compound callsigns included.

**Direct connection to the site (Settings → UaHam Site).** WSJT-Z hands every logged contact to the award pages on uahamaward.com itself, whether you logged it by hand or auto-sequencing did. **The separate bridge program is no longer needed:** nothing to download, nothing to keep updated. With no log page open nothing is sent, and logging works exactly as it always did.

**Ukrainian interface (Settings → Language).** The main window, menus, settings, the QSO logging dialog and error windows are translated. Mode names, band names, units and on-air abbreviations are deliberately left in English. The language takes effect on the next start.

**A "UaHam" tab in the main window** shows the filter mode, how many decodes were hidden, whether a browser is connected and how many QSOs were sent. The same in short in the status bar.

## Fixed in inherited code

The filtering flag was cleared once per batch of decodes instead of once per decode. One filtered signal in a period was therefore enough to hide every later decode in the same batch, and to suppress auto-sequencing with them.

## Installing

Windows — `.exe`. Linux — `.deb` or `.rpm` for your architecture.
