## Що це

Збірка **WSJT-Z** з інтеграцією [uahamaward.com](https://uahamaward.com). Усе інше — оригінальний WSJT-Z від SQ9FVE, без змін.

Це **не офіційний реліз WSJT-Z**. Про проблеми саме з тим, що описано нижче, пишіть сюди, а не авторам WSJT-Z чи WSJT-X.

## Що змінилось від `uaham2`

Одне виправлення, і його чути в ефірі. Якщо ви даєте CQ з увімкненою галочкою **«Apply filtering to stations calling us»**, станція, з якою ви щойно провели зв'язок, могла обійти ваші фільтри й затягнути вас у друге автоматичне QSO. Досить було, щоб вона відповіла самим лише рапортом — `-10`, `R-10`, `RR73` чи `73`. У такому пакеті немає локатора, тому жодна з наступних перевірок за нього не бралася, і автопослідовність відповідала так, ніби фільтрів не існує.

Тепер, поки ви кличете CQ, така станція проходить ті самі фільтри, що й будь-яка інша. На зв'язок, який уже почався, це не впливає: доки QSO триває, ваш кореспондент лишається поза фільтрами — інакше ви б втратили другу половину власного зв'язку. Якщо галочку вимкнено, не змінюється нічого: вона й далі означає рівно те, що написано в її підказці.

Знайшов і виправив Дмитро Данилченко ([@ddanilchenko](https://github.com/ddanilchenko)) — [PR #1](https://github.com/uaro-radio/wsjt-z/pull/1). Дякуємо.

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

## Changed since `uaham2`

One fix, and it is audible on the air. When you call CQ with **"Apply filtering to stations calling us"** switched on, a station you had just worked could slip past your filters and pull you into a second automatic QSO. All it took was an answer carrying nothing but a report — `-10`, `R-10`, `RR73` or `73`. Such a message has no grid square, so none of the later checks would look at it, and auto-sequencing replied as though the filters were not there.

While you are calling CQ that station now goes through the same filters as anyone else. A QSO already under way is untouched: for as long as it runs your correspondent stays exempt from filtering, or you would lose the second half of your own contact. With the setting off nothing changes at all — it still means exactly what its tooltip says.

Found and fixed by Dmitry Danilchenko ([@ddanilchenko](https://github.com/ddanilchenko)) in [PR #1](https://github.com/uaro-radio/wsjt-z/pull/1). Thank you.

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
