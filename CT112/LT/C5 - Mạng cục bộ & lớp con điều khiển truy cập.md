# Mạng cục bộ & lớp con điều khiển truy cập

# Giới thiệu

Phân loại mạng theo khoảng cách địa lý:

- Mạng cục bộ - Local Area Network (LAN)
- Mạng đô thị - Metropolitan Area Network (MAN)
- Mạng diện rộng - Wide Area Network (WAN)

Trong thực tế mạng LAN và WAN thường được cài đặt nhất, đặc biệt là mạng LAN

Chuẩn chung cho mạng LAN là IEEE 802.X; được sử dụng nhiều nhất là Ethernet (802.3), Wireless LAN (802.11), Token Ring (802.5).

_IEEE : Institute of Electrical and Electronics Engineers_

## Đặc tính

- Tất cả các host trong mạng LAN cùng chia sẻ đường truyền chung.
- Hoạt động dựa trên kiểu quảng bá (Broadcast).
- Không yêu cầu phải có hệ thống trung chuyển (routing/switching) trong một LAN đơn.

## Thông số

- Hình trạng (topology): xác định topology kết nối của các host trong một mạng LAN
- Đường truyền chung (Shared channel): xác định loại kênh được sử dụng để kết nối các host trong mạng LAN (xoắn đôi, đồng trục, cáp quang)
- Kỹ thuật truy cập đường truyền (Medium Access Control - MAC): xác định cách thức/phương pháp mà các host sử dụng để chia sẻ một kênh chung trong mạng LAN
- MAC quản lý việc truy cập đến đường truyền trong LAN và cung cấp cơ sở cho việc định danh các tính chất của mạng LAN theo chuẩn IEEE.

# MAC sublayer

## Kênh truyền đa truy cập (Multiple Access Links)

Có 3 loại kênh truyền:

- Point – to – point (single wire, e.g. PPP, SLIP)
- Broadcast (shared wire or medium; e.g, Ethernet, Wavelan, etc)
- Switched (switched Ethernet, ATM )

## Vấn đề đa truy cập trong mạng LAN:

- Một kênh giao tiếp được chia sẻ
- Hai hay nhiều nút cùng truyền tin đồng thời sẽ dẫn đến giao thoa tín hiệu ⇒ tạo ra trạng thái lỗi
  - Chỉ cho phép một trạm truyền tin thành công tại một thời điểm
  - Cần có giao thức chia sẻ đường truyền chung giữa các nút trong mạng, gọi là giao thức điều khiển truy cập đường truyền (MAC Protocol)

## MAC Protocol trong mô hình OSI:

![Untitled](./.image/c5/Untitled.png)

- Tầng liên kết dữ liệu được chia thành hai tầng con:
  - Tầng điều khiển kênh truyền luận lý (Logical Link Control Layer )
  - Tầng điều khiển truy cập đường truyền (Medium Access Control Layer)

### Logical Link Control Layer

- Giao tiếp với tầng mạng
- Điều khiển lỗi và điều khiển luồng
- Dựa trên giao thức HDLC
- Cung cấp 03 loại dịch vụ:
	- Unacknowledged connectionless service (dịch vụ không kết nối không báo nhận)
	- Connection mode service - acknowledged connection-oriented service (dịch vụ kết nối - dịch vụ định hướng kết nối có báo nhận)
	- Acknowledged connectionless service (dịch vụ không kết nối có báo nhận)

### Medium Access Control Layer

- Tập hợp dữ liệu thành khung cùng với trường địa chỉ nhận/gởi, chuỗi kiểm tra khung
- Phân tách dữ liệu khung nhận được với trường địa chỉ và thực hiện kiểm tra lỗi
- Điều khiển việc truy cập đường truyền: Một điều không có trong tầng liên kết dữ liệu truyền thống
- Cùng một tầng LLC có thể có nhiều tùy chọn cho tầng MAC

## Các giao thức mạng LAN trong ngữ cảnh chung

![Untitled](./.image/c5/Untitled%201.png)

## Giao thức điều khiển truy cập đường truyền

[Phương pháp chia kênh (Channel Partitioning)](https://www.notion.so/Ph-ng-ph-p-chia-k-nh-Channel-Partitioning-2ebc8424bcc881469b12d9d1ae8898c1?pvs=21)

- Phân chia kênh truyền thành nhiều phần nhỏ (time slots, frequency, code)
- Cấp phát những phần nhỏ này cho các nút sử dụng một cách loại trừ nhau

[Phương pháp truy cập đường truyền ngẫu nhiên (Random Access)](https://www.notion.so/Ph-ng-ph-p-truy-c-p-ng-truy-n-ng-u-nhi-n-Random-Access-2ebc8424bcc8813895b9f85d32f06c96?pvs=21)

- Cho phép đụng độ
- Phục hồi lại sau đụng độ

[Phương pháp phân lượt (Taking turns)](https://www.notion.so/Ph-ng-ph-p-ph-n-l-t-Taking-turns-2ebc8424bcc881119f27e66ccec2f150?pvs=21)

- Hợp tác chặt chẽ trong việc truy cập kênh truyền được chia sẻ để tránh đụng độ

# Một số chuẩn mạng cục bộ

## Chuẩn hóa mạng cục bộ

![Untitled](./.image/c5/Untitled%202.png)

- MAC quản lý việc truy cập đường truyền
- LLC đảm bảo tính độc lập của việc quản lý các liên kết dữ liệu với đường truyền vật lý & phương pháp truy cập đường truyền.
- IEEE (Institute of Electrical and Electronic Engineers)
	- Tổ chức đi tiên phong trong lĩnh vực chuẩn hóa mạng cục bộ
	- Dự án IEEE 802 định nghĩa các chuẩn thuộc họ IEEE 802.x

![Untitled](./.image/c5/Untitled%203.png)

## Chuẩn mạng Ethernet 802.3

![Picture1.png](./.image/c5/Picture1.png)

![Untitled](./.image/c5/Untitled%204.png)

- Bức phác họa Ethernet của Bob Metcalfe, người sáng lập ra Ethernet

(Xerox PARC - 1972)

![Untitled](./.image/c5/Untitled%205.png)

- Preamble: dài 7 bytes với mẫu 10101010 được sử dụng để đồng bộ hóa tốc độ đồng hồ giữa bên gởi và bên nhận, theo sau bởi 1 byte với mẫu 10101011 được gọi là byte SFD (Start Frame Delimiter)
- Source and dest. addresses: Địa chỉ nguồn và đích, gồm 6 bytes được biểu diễn như sau:
  - Hệ hex (16): 08:00:2b:e4:b1:02 hoặc 08-00-2b-e4-b1-02
  - Hệ nhị phân: 00001000 00000000 00101011 11100100 10110001 00000010
- Khuôn dạng địa chỉ MAC được chia làm 2 phần:
  - 3 bytes đầu xác định hãng sản xuất, chịu sự quản lý của tổ chức IEEE.
  - 3 bytes sau do nhà sản xuất ấn định.
- Địa chỉ đích có thể là dạng Unicast, Multicast hay Broadcast.
- Type: chỉ ra giao thức được sử dụng ở tầng cao hơn, thường là IP, nhưng các giao thức khác vẫn được hỗ trợ - ví dụ: Novell IPX và AppleTalk.
- Data: chứa dữ liệu của tâng bên trên, tối đa là 1500 bytes
- CRC: Phần kiểm tra lỗi. Lỗi được kiểm tra tại trạm đích. Nếu khung có lỗi, nó sẽ bị xóa.

Sử dụng phương pháp mã hóa đường truyền Manchester

![Untitled](./.image/c5/Untitled%206.png)

### Giải thuật truy cập đường truyền: CSMA/CD + Exponential back-off

```c
Nhận một gói tin từ tầng cao hơn;
K := 0; n :=0; // K: tg chờ đợi ngẫu nhiên; n: số vụ đụng độ đã gặp phải
repeat:
Chờ trong khoảng thời gian K*512 bit-time; // = 52.1micros chờ khe tgian ngẫu nhiên kế tiếp
While (đường truyền bận)
	wait;
Chờ tiếp 96 bit-time (9.6micros) sau khi nhận thấy không có tín hiệu trên đtruyền;
Truyền khung và chú ý phát hiện đụng độ;
If (có đụng độ){
	ngừng truyền và phát tiếp một dãy nhồi 48-bit;
	n++;
	m:= min(n, 10);
	chọn K ngẫu nhiên từ tập hợp {0, 1, 2, …, 2m-1};
	if (n < 16) goto repeat;
	else bỏ việc truyền;
}
```

![Untitled](./.image/c5/Untitled%207.png)

# Một số chuẩn mạng cục bộ

## Ethernet 802.3

| Tên     | Sử dụng cáp             | Chế độ truyền | Tốc độ tối đa | Băng tần | Chiều dài tối đa | Mã hóa     | Chuẩn mạng     |
| ------- | ----------------------- | ------------- | ------------- | -------- | ---------------- | ---------- | -------------- |
| 10Base5 | cáp đồng trục loại dày  | half duplex   | 10 Mb/s       | cơ sở    | 500m             | Manchester | Ethernet 802.3 |
| 10Base2 | cáp đồng trục loại mỏng | half duplex   | 10 Mb/s       | cơ sở    | 185m             | Manchester | Ethernet 802.3 |
| 10BaseT | UTP Cat 3 trở lên       |               | 10 Mb/s       |          | 100m             |            | Ethernet 802.3 |
| 10BaseF | cáp quang               |               | 10 Mb/s       |          | 2000m            |            | Ethernet 802.3 |

## Ethernet 802.3u

| Tên        | Sử dụng cáp       | Chế độ truyền | Tốc độ tối đa | Băng tần | Chiều dài tối đa | Mã hóa | Chuẩn mạng      |
| ---------- | ----------------- | ------------- | ------------- | -------- | ---------------- | ------ | --------------- |
| 100BaseTX  | UTP Cat 5 trở lên |               | 100 Mb/s      |          | 100m             | 4B/5B  | Ethernet 802.3u |
| 100BaseFX  | cáp quang         |               | 100 Mb/s      |          | 2000m            | 4B/5B  | Ethernet 802.3u |
| 1000BaseSX | multimode         |               | 1000 Mb/s     |          | 550m             | 8B/10B | Ethernet 802.3u |
| 1000BaseLX | singlemode        |               | 1000 Mb/s     |          | 10km             | 8B/10B | Ethernet 802.3u |
| 1000BaseCX | STP               |               | 1000 Mb/s     |          | 25m              | 8B/10B | Ethernet 802.3u |

## 10Gigabit Ethernet

| Tên        | Sử dụng cáp       | Chế độ truyền | Tốc độ tối đa | Băng tần | Chiều dài tối đa | Mã hóa  | Chuẩn mạng         |
| ---------- | ----------------- | ------------- | ------------- | -------- | ---------------- | ------- | ------------------ |
| 10GBase-SR | multimode         | full duplex   | 10Gbps        |          | 300m             | 65B/66B | 10Gigabit Ethernet |
| 10GBase-LR | singlemode        | full duplex   | 10Gbps        |          | 10km             | 65B/66B | 10Gigabit Ethernet |
| 10GBase-T  | UTP Cat 6 trở lên |               | 10Gbps        |          | 55m / 100m       | LDPC    | 10Gigabit Ethernet |
