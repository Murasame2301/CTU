# Chương 1: TỔNG QUAN VỀ AN TOÀN HỆ THỐNG & AN NINH MẠNG
---

## I) KHÁI NIỆM CƠ BẢN

### An toàn là gì?

- **An toàn (Security)** là một quá trình liên tục bảo vệ một đối tượng khỏi các tấn công, không phải là trạng thái tĩnh mà là hành trình không ngừng.
- **An toàn thông tin (Information Security)** là khả năng bảo vệ môi trường thông tin kinh tế – xã hội, đảm bảo việc hình thành, sử dụng và phát triển thông tin vì lợi ích của mọi công dân, tổ chức và quốc gia.
- **An toàn máy tính (Computer Security)** bảo vệ toàn bộ tài nguyên của hệ thống máy tính gồm phần cứng vật lý (CPU, màn hình, bộ nhớ…) và phần mềm, dữ liệu bên trong.
- **An toàn mạng (Network Security)** là an toàn thông tin trong không gian mạng máy tính.

---

### Tam giác CIA – Mục tiêu cốt lõi

Ba mục tiêu cần đạt được của một hệ thống an toàn, thường gọi là **CIA Triad**:

| Mục tiêu | Tên tiếng Anh | Ý nghĩa |
|---|---|---|
| **Bảo mật** | Confidentiality | Dữ liệu không bị truy xuất hay theo dõi trái phép |
| **Toàn vẹn** | Integrity | Dữ liệu không bị thay đổi hay phá hoại |
| **Sẵn dùng** | Availability | Hệ thống và tài nguyên luôn thông suốt khi cần |

> **📌 Cập nhật 2026:** Nhiều tài liệu hiện đại mở rộng CIA thành **CIA + AAA + NR (Non-Repudiation)** hoặc mô hình **Parkerian Hexad** bổ sung tính xác thực (Authenticity), sở hữu (Possession/Control) và tiện ích (Utility). Tính chống chối bỏ (Non-Repudiation) ngày càng quan trọng trong giao dịch điện tử và chữ ký số.

---

## II) TẤN CÔNG TRÊN MẠNG

### Phân loại mối đe dọa (Threat)

Mối đe dọa có thể phân theo 4 nhóm như sau:

**Theo tổ chức:**
- **Có tổ chức (Structured)** – Được hoạch định dài hạn bởi hacker thành thạo, khó phát hiện vì được che giấu kỹ.
- **Không tổ chức (Unstructured)** – Hacker đơn lẻ, dùng công cụ có sẵn trên Internet để thử nghiệm.

**Theo vị trí:**
- **Từ bên ngoài** – Qua Internet hoặc Dial-up, không có quyền truy cập hệ thống.
- **Từ bên trong** – Người có quyền truy cập nội bộ. Thống kê: **70% vấn đề bảo mật đến từ nội bộ**.

**Theo chủ động/thụ động:**
- **Chủ động (Active)** – Có thể sửa đổi thông tin hoặc thay đổi trạng thái hệ thống (VD: thay bảng vạch đường Router).
- **Thụ động (Passive)** – Chỉ nghe lén mà không thay đổi dữ liệu (VD: nghe trộm đường truyền).

**Theo cố ý/vô tình:**
- **Cố ý (Intentional)** – Tấn công tinh vi có chủ đích (VD: xâm nhập mạng trái phép).
- **Vô tình (Unintentional)** – Sự kiện ngẫu nhiên gây hại (VD: chế độ đặc quyền tự động login).

---

### Phân loại Hacker

| Loại | Màu mũ | Mô tả |
|---|---|---|
| White Hat | Trắng | Xâm nhập có ý tốt (nhà bảo mật, pen-tester được ủy quyền) |
| Black Hat | Đen | Thâm nhập với mục đích xấu, phá hoại, đánh cắp |
| Gray Hat | Xám | Đôi khi trắng, đôi khi đen |
| Blue Hat | Xanh | Chuyên gia được thuê để tìm lỗi trước khi phát hành |
| Cracker | — | "Criminal Hacker" – hacker tội phạm |

> **📌 Cập nhật 2026:** Xuất hiện thêm:
> - **Script Kiddie** – Người dùng công cụ có sẵn mà không hiểu nguyên lý.
> - **Hacktivists** – Tấn công vì lý do chính trị/xã hội (VD: nhóm Anonymous).
> - **Nation-State Hackers** – Hacker được nhà nước bảo trợ, đứng sau các cuộc tấn công APT (Advanced Persistent Threat).
> - **Bug Bounty Hunter** – Người hợp pháp tìm lỗi để nhận thưởng từ các tổ chức.

---

### Ba loại tấn công chính

#### 1. Tấn công do thám (Reconnaissance)

**Khái niệm:** Không chiếm đoạt hệ thống, chỉ thu thập thông tin (địa chỉ IP, cổng mở, hệ điều hành, phiên bản web server…) để chuẩn bị cho các bước tấn công sau.

**Các kỹ thuật do thám:**

| Kỹ thuật | Mô tả | Công cụ |
|---|---|---|
| Nghe lén (Sniffer) | Bắt gói tin trên đường truyền | Wireshark, Ngrep, Dsniff |
| Quét địa chỉ IP (Ping Sweep) | Gửi ICMP request để tìm host đang hoạt động | Fping, Pinger, Network Sonar |
| Quét cổng (Port Sweep) | Xác định cổng và dịch vụ đang mở | Nmap, Nessus, SuperScan |
| Quét tránh né (Evasive Sweep) | Quét bằng cờ FIN, không tạo kết nối, không ghi log | Nmap, IPEye, AWSPS |
| Xác định hệ điều hành (OS ID) | Dựa vào sự khác biệt triển khai TCP/IP | Nmap, Queso |

**Phân loại cổng:**
- **Well-known port:** 0 – 1023
- **Registered port:** 1024 – 49151
- **Private port:** 49152 – 65535

> **📌 Cập nhật 2026:** Wireshark và Nmap vẫn là tiêu chuẩn ngành. Bổ sung thêm: **Shodan** (tìm kiếm thiết bị IoT lộ ra Internet), **OSINT Framework** (thu thập thông tin từ nguồn mở), **Censys**. Kỹ thuật **passive reconnaissance** qua mạng xã hội (LinkedIn, Facebook) ngày càng được ưa chuộng vì không để lại dấu vết. ⚠️ **Ethereal đã ngừng phát triển**, được thay hoàn toàn bởi Wireshark.

---

#### 2. Tấn công truy cập (Access Attack)

**Khái niệm:** Chiếm lấy tài nguyên trên hệ thống đích như file, mật khẩu, quyền điều khiển. Thực hiện sau bước do thám.

**Các kỹ thuật tấn công truy cập:**

**Nghe lén (Sniffing)**
- Trong môi trường **Hub**: Sniffer bắt tất cả gói tin, kể cả không gửi cho mình.
- Trong môi trường **Switch** dùng các kỹ thuật vượt qua:
  - **ARP Spoofing** – Giả dạng Gateway, gửi ARP Reply giả cho các máy trong LAN.
  - **MAC Duplicating** – Thay đổi địa chỉ MAC giống máy đích để switch chuyển nhầm gói.
  - **CAM Table Flooding** – Gửi hàng loạt MAC giả làm đầy bảng CAM, switch hoạt động như Hub.
  - **DNS Spoofing** – Gửi DNS Reply giả để chuyển hướng traffic.
- Công cụ: Ettercap, Wireshark.

**Sử dụng lại (Replay)**
Ghi lại thông tin chứng thực (username/password) rồi dùng lại sau để xâm nhập.

**Cướp giao dịch (Session Hijacking)**
Chiếm quyền điều khiển phiên đang diễn ra (thường qua cookie). Công cụ: Juggernaut, ttywatcher, jhijack.

**Kẻ đứng giữa (Man-in-the-Middle)**
Chặn và thay thế gói dữ liệu giữa hai bên, là dạng tấn công giả mạo (Spoofing). Công cụ: Ettercap, Burp Suite.

**Cổng sau (Backdoor)**
Cài chương trình server trên máy nạn nhân để truy cập về sau, kể cả khi xâm nhập trước đó đã bị phát hiện. VD: BackOrifice, NetBus, Subseven. *(Đã lỗi thời)*

**Đánh lừa (Social Engineering)**
Khai thác điểm yếu **con người**, không cần tấn công kỹ thuật.

**Lừa đảo (Phishing)**
Dạng social engineering qua email và website giả mạo dẫn dắt người dùng nhập thông tin cá nhân.

**Giả dạng (Spoofing)**
- **DNS Spoofing** – Chèn dữ liệu DNS giả vào cache của DNS resolver, chuyển hướng người dùng sang website lừa đảo.
- **ARP Spoofing** – Liên kết MAC của hacker với IP hợp pháp, dùng trong DoS và Man-in-the-Middle.
- **IP Spoofing** – Giả mạo địa chỉ IP nguồn, chủ yếu dùng trong tấn công DDoS.

**Khai thác lỗi (Exploitation)**
Khai thác điểm yếu của công nghệ, giao thức (TCP/IP, UDP, ICMP, SNMP, SMTP…) hoặc lỗi hệ điều hành chưa vá.

**Tràn bộ đệm (Buffer Overflow)**
Ghi dữ liệu vượt kích thước bộ đệm, ghi đè địa chỉ trở về (Return Address) trong Stack để kích hoạt mã độc tùy ý. Theo Sophos, hơn **28%** lỗi bảo mật là lỗi tràn bộ đệm.

*Lịch sử nổi bật:* Sâu Morris (1988), Code Red khai thác IIS 5.0 (2001), SQLSlammer khai thác SQL Server 2000 (2003).

**Tấn công mật khẩu (Password Attack)**

Các lỗi thường gặp khi đặt mật khẩu:
- Không đổi mật khẩu mặc định
- Mật khẩu quá ngắn hoặc quá thông dụng
- Liên quan thông tin cá nhân (ngày sinh, tên con…)

Các phương pháp tấn công:
- **Nghe lén** trên đường truyền
- **Dự đoán** (Guessing)
- **Dò từ điển** (Dictionary-based)
- **Vét cạn** (Brute Force)

Công cụ: L0phtCrack, Brutus, Hydra, Cain And Abel, John the Ripper.

**SQL Injection**
Chèn câu lệnh SQL bất hợp pháp qua form nhập liệu (username/password) để liệt kê, chỉnh sửa hoặc xóa dữ liệu trong cơ sở dữ liệu. VD: nhập `' OR ''='` vào cả hai ô username và password sẽ liệt kê toàn bộ bảng người dùng.

> **📌 Cập nhật 2026:**
> - BackOrifice, NetBus, Subseven **lỗi thời hoàn toàn**. RAT hiện đại: Cobalt Strike, Metasploit, Sliver C2 (dùng trong red teaming hợp pháp).
> - Session Hijacking khó hơn do HTTPS nhưng vẫn xảy ra qua **XSS (Cross-Site Scripting)**.
> - SQL Injection vẫn trong **OWASP Top 10** nhưng nay còn có **NoSQL Injection**, **GraphQL Injection**.
> - Buffer Overflow khó hơn do ASLR, DEP, Stack Canaries – nhưng kỹ thuật **ROP (Return-Oriented Programming)** vượt qua được.
> - Phishing tinh vi hơn: **Spear Phishing** (nhắm mục tiêu cụ thể), **Whaling** (nhắm CEO/lãnh đạo), **Vishing** (qua điện thoại), **Smishing** (qua SMS), **Deepfake phishing** (dùng AI giả giọng/hình ảnh).

---

#### 3. Tấn công từ chối dịch vụ (DoS / DDoS)

**Khái niệm:** Mục đích phá hoại, ngăn người dùng hợp pháp sử dụng dịch vụ. Không nhằm đánh cắp thông tin mà làm Server không thể đáp ứng yêu cầu.

**Các kỹ thuật DoS:**

| Kỹ thuật | Mô tả |
|---|---|
| SYN Flood | Gửi hàng loạt SYN giả, server dành tài nguyên chờ ACK không đến → cạn kiệt |
| UDP Flood | Gửi gói UDP echo với địa chỉ nguồn là loopback của mục tiêu |
| Làm quá tải dịch vụ | Gửi hàng loạt request đến web server hoặc email đến một tài khoản |

**DDoS (Distributed DoS):**
Dùng nhiều máy bị kiểm soát (**Botnet**) tấn công cùng lúc. Công cụ cũ: Trinoo, Stacheldraht, TFN2K, Mstream.

**Bốn hình thức tấn công cơ bản trên mạng:**

| Hình thức | Tấn công vào | Mô tả |
|---|---|---|
| Ngăn chặn (Interruption) | Tính sẵn dùng | Tài nguyên bị phá hủy, không sẵn sàng phục vụ |
| Đánh chặn (Interception) | Tính bí mật | Kẻ tấn công truy nhập tới tài nguyên thông tin |
| Sửa đổi (Modification) | Tính toàn vẹn | Truy nhập và chỉnh sửa thông tin trên mạng |
| Chèn giả mạo (Fabrication) | Tính xác thực | Chèn thông tin và dữ liệu giả vào hệ thống |

> **📌 Cập nhật 2026:** DDoS ngày càng lớn, năm 2023–2025 ghi nhận các cuộc tấn công vượt **1 Tbps**. Xu hướng mới:
> - **HTTP/2 Rapid Reset Attack** – Khai thác đặc điểm HTTP/2, kỷ lục 2023.
> - **Amplification Attack** – DNS/NTP Amplification khuếch đại lưu lượng tấn công lên hàng trăm lần.
> - **Botnet IoT** – Mirai và hậu duệ chiếm dụng thiết bị IoT bảo mật yếu.
> - ⚠️ Jolt2, Targa, Bubonic.c **gần như không còn được sử dụng**.
> - Các dịch vụ chống DDoS như **Cloudflare**, **AWS Shield** đã trở thành tiêu chuẩn.

---

## III) CÁC PHẦN MỀM CÓ HẠI (MALWARE)

### Phân loại Malware

| Loại | Đặc điểm chính | Tự lây lan? | Nguy hiểm chính |
|---|---|---|---|
| **Virus** | Tự nhân bản, bám vào file | Có (qua file/email) | Phá hoại phần cứng, phần mềm |
| **Worm** | Lan qua mạng, không cần file host | Có (qua mạng) | Làm tràn băng thông, cạn tài nguyên |
| **Trojan** | Giả dạng phần mềm hợp lệ | Không | Lấy cắp thông tin, cài backdoor |
| **Adware** | Hiện quảng cáo tự động | Không | Làm phiền, thay đổi trình duyệt |
| **Spyware** | Theo dõi và đánh cắp thông tin | Không | Lộ thông tin cá nhân |
| **Keylogger** | Ghi lại thao tác bàn phím | Không | Đánh cắp mật khẩu |
| **Rootkit** | Ẩn giấu sự hiện diện của malware | Không | Kiểm soát hoàn toàn hệ thống |
| **Cookie** | Lưu thông tin phiên duyệt web | Không | Tiết lộ thói quen duyệt web |

### Chi tiết từng loại

**Virus** – Phân loại: Boot virus (đã lỗi thời, lây qua đĩa mềm), File virus (lây qua .exe/.com/.bat/.sys/.pif), Macro virus (lây qua file Office), lây qua Email (.exe, .js, Script), lây qua Internet (ẩn trong phần mềm crack/freeware). Nổi tiếng: Jerusalem, CIH/Chernobyl, ILoveYou, Anna Kournikova, Sircam, Benjamin.

**Worm** – Khác virus ở chỗ có đặc tính phá hoại mạng, làm tăng lưu thông, chiếm băng thông và tài nguyên Server. Kết hợp DDoS gây tác hại rất lớn. Nổi tiếng: Mellisa (1999), Love Letter (2000), Nimda, Code Red (2001), SQL Slammer, Blaster (2003), Sasser (2004), Zotob (2005).

**Trojan** – Không có tính chất lây lan, lừa nạn nhân tự chạy. Thường có trong file crack và keygen. VD: BackOrifice, NetBus, Subseven *(đã lỗi thời)*.

**Spyware & Adware** – Nguyên nhân nhiễm: phần mềm freeware/shareware, chấp nhận cài ActiveX lạ, trình duyệt chưa vá lỗi, cấu hình bảo mật trình duyệt thấp, bị lây từ malware khác.

**Keylogger** – Ghi lại thao tác bàn phím, ảnh màn hình, chuyển động chuột. Xếp vào nhóm phần mềm gián điệp. Nổi tiếng: Perfect Keylogger, Spytector, KeyLog, Remote Keylogger.

**Rootkit** – Che giấu sự tồn tại của file/quá trình, máy bị nhiễm được coi là bị chiếm quyền root, thường đi kèm nhiều Backdoor, công cụ hệ điều hành thông thường không phát hiện được.

**Cookie** – Thông tin lưu trên máy tính để nhận dạng người dùng khi duyệt web. Là dạng Spyware nhưng **không hoàn toàn xấu** (hữu ích cho trải nghiệm người dùng).

> **📌 Cập nhật 2026:**
> - **Boot virus** gần như biến mất.
> - **Macro virus** giảm mạnh sau khi Microsoft chặn macro mặc định từ năm 2022.
> - **BackOrifice, NetBus, Subseven** lỗi thời hoàn toàn. RAT hiện đại: Cobalt Strike, Metasploit Framework, Sliver C2.
> - Xu hướng mới nổi bật:
>   - **Ransomware** – Mã hóa dữ liệu đòi tiền chuộc, tấn công hạ tầng quan trọng (bệnh viện, đường ống dầu). **Ransomware as a Service (RaaS)** cho thuê công cụ tấn công.
>   - **Fileless Malware** – Tồn tại trong RAM, không ghi file, rất khó phát hiện bằng antivirus truyền thống.
>   - **Cryptojacking** – Chiếm dụng CPU để đào tiền ảo mà người dùng không hay.
>   - **AI-powered Malware** – Malware tự thích nghi, tránh né phát hiện.
>   - **Supply Chain Attack** – Tấn công vào nhà cung cấp phần mềm để lan rộng đến hàng nghìn nạn nhân (VD: SolarWinds 2020, XZ Utils 2024).

---

## IV) YÊU CẦU CỦA HỆ THỐNG MẠNG AN TOÀN

### Kiến trúc AAA

**AAA** là nền tảng của hệ thống mạng an toàn, gồm ba thành phần:

| Thành phần | Tiếng Việt | Chức năng |
|---|---|---|
| **Authentication** | Chứng thực | Nhận dạng đúng người dùng – *Who are you?* |
| **Authorization** | Phân quyền | Giới hạn quyền người dùng có thể làm – *What can you do?* |
| **Accounting** | Giám sát | Theo dõi những gì người dùng đã làm – *What did you do?* |

AAA cung cấp phương thức định danh người dùng, xác định mức độ truy cập và giám sát hoạt động trong mạng.

---

### Authentication (Chứng thực)

**Khái niệm:** Quy trình xác minh nhận dạng số (digital identity) của bên gửi thông tin trong giao tiếp.

**Điểm yếu của hệ thống tài khoản-mật khẩu truyền thống:** mật khẩu có thể bị quên, bị lộ, hoặc dễ dàng dò tìm nếu đặt yếu.

#### Chứng thực 1 chiều vs 2 chiều

| Loại | Mô tả |
|---|---|
| **1 chiều (1-way)** | Client cung cấp username/password cho Server |
| **2 chiều (2-way)** | Cả hai bên xác nhận với nhau bằng username/password tương ứng |

#### Các giao thức và phương thức chứng thực

**PAP (Password Authentication Protocol)**
- Chứng thực 1 hoặc 2 chiều.
- Gửi username/password dạng **plaintext** trực tiếp trên đường truyền.
- **Kém an toàn.** *(Không còn khuyến dùng)*

**CHAP (Challenge Handshake Authentication Protocol)**
- Chứng thực 2 chiều.
- Không gửi trực tiếp mật khẩu, dùng **mã hóa MD5**.
- An toàn hơn PAP. *(Nhưng MD5 ngày nay đã bị coi là yếu)*

**Kerberos**
- Hệ thống chứng thực bên thứ ba tin cậy (trusted third-party).
- Dùng **session key có thời gian sống ngắn**, chống replay attack.
- Không truyền mật khẩu plaintext trên mạng.
- Phát triển bởi MIT từ 1980, tích hợp trong Windows (Active Directory), Solaris, router Cisco.

Hoạt động qua 3 pha:
1. Client giao tiếp với **AS (Authentication Server)** → nhận **TGT (Ticket Granting Ticket)**.
2. Dùng TGT giao tiếp với **TGS (Ticket Granting Server)** → nhận **Service Ticket**.
3. Dùng Service Ticket truy cập **Application Server**.

*Lưu ý:* Cần đồng bộ hóa đồng hồ giữa các máy, và cần nhiều máy chủ để đảm bảo không ngưng trệ.

**OTP (One Time Password)**
- Mật khẩu dùng **một lần**, người dùng không lo bị đánh cắp hay mất mật khẩu.
- Thường đi kèm thiết bị phần cứng đồng bộ thời gian với server xác thực.

**Token Card**
- Một trong các giải pháp bảo mật an toàn nhất.
- Dùng kết hợp với PIN/mật khẩu.
- Thiết bị: thẻ cứng, PC card, USB, Bluetooth.

**Biometrics (Sinh trắc học)**
- Đặc điểm sinh học: khuôn mặt, bàn tay, mống mắt, võng mạc, vân tay, DNA.
- Hành vi: dáng đi, chữ ký, giọng nói.
- Ưu điểm: không thể mất, không thể quên, rất khó giả mạo.
- Nhược điểm: thiết bị đọc không chính xác, đặc điểm có thể thay đổi theo năm tháng.

> **📌 Cập nhật 2026:**
> - **PAP hầu như không còn được dùng** trong môi trường hiện đại.
> - **CHAP/MD5** bị coi là yếu, đang bị thay thế.
> - **MFA (Multi-Factor Authentication)** là tiêu chuẩn mới: kết hợp ít nhất 2 trong 3 yếu tố: *thứ bạn biết* (mật khẩu) + *thứ bạn có* (token/điện thoại) + *thứ bạn là* (sinh trắc học).
> - **Passwordless Authentication** qua **FIDO2/WebAuthn** đang được Microsoft, Google thúc đẩy mạnh.
> - Kerberos vẫn còn nhưng có lỗ hổng **Kerberoasting**, **AS-REP Roasting** đang bị khai thác nhiều.

---

### Authorization (Phân quyền)

**Khái niệm:** Định nghĩa các quyền (rights) và sự cho phép (permission) của người dùng sau khi đã được chứng thực.

#### DAC vs MAC vs RBAC

| Kiểu | Tên đầy đủ | Người quyết định quyền | Áp dụng |
|---|---|---|---|
| **DAC** | Discretionary Access Control | Chủ nhân tài nguyên | Linux, Windows |
| **MAC** | Mandatory Access Control | Hệ thống | Môi trường bảo mật cao (quân sự) |
| **RBAC** | Role-Based Access Control | Vai trò trong tổ chức | Doanh nghiệp |

**DAC** – Dùng ACL (Access Control List) hoặc RBAC. Root/Administrator có toàn quyền.

**MAC** – Dùng cho hệ thống đa tầng: Top Secret → Secret → Classified → Unclassified. Chủ thể phải có mức tin cẩn **tương đồng hoặc cao hơn** mức đối tượng cần truy cập.

**RBAC** – Người dùng không được cấp quyền trực tiếp mà nhận quyền thông qua vai trò (role) trong tổ chức → việc quản lý quyền đơn giản hơn.

#### Các mô hình bảo mật thông tin

**Mô hình Bell-LaPadula**
- Đảm bảo **tính bí mật** của dữ liệu.
- Nguyên tắc: **No Read Up** (không đọc dữ liệu cấp cao hơn), **No Write Down** (không ghi xuống cấp thấp hơn).
- Điểm yếu: không đảm bảo tính toàn vẹn.

**Mô hình Biba**
- Đảm bảo **tính toàn vẹn** của dữ liệu (bổ sung điểm yếu của Bell-LaPadula).
- Nguyên tắc: **No Read Down** (không đọc cấp thấp hơn), **No Write Up** (không ghi lên cấp cao hơn).

**Mô hình Clark-Wilson**
- Giải quyết **tính toàn vẹn** của dữ liệu qua hai quy trình:
  - **Transformation Process** – Tiếp nhận yêu cầu truy cập và chuyển đổi thành mô tả quyền hạn.
  - **Integration Verification Process** – Thực hiện xác thực và trao quyền.
- Chia dữ liệu thành: *Có ràng buộc* (cần điều kiện mới truy cập) và *Không ràng buộc* (mọi chủ thể đều truy cập được).

---

### Accounting (Giám sát)

**Mục đích:** Ghi nhận dấu vết xâm nhập để cung cấp bức tranh rõ ràng về các sự kiện đã xảy ra trong hệ thống.

**Ba hình thức giám sát chính:**

| Hình thức | Mô tả |
|---|---|
| **Logging** (Ghi nhật ký) | Ghi lại sự kiện và thời điểm xảy ra. Lưu dạng text, ghi liên tục, có thể gửi về SysLog Server |
| **Scanning** (Quét hệ thống) | Theo dõi và kiểm tra các dịch vụ mạng đang hoạt động, phát hiện điểm yếu |
| **Monitoring** (Kiểm soát) | Thường xuyên xem lại log file, dùng công cụ phân tích log và cảnh báo nguy cơ |

**Lưu ý về Logging:**
- Lưu dạng file text, từng dòng là một sự kiện.
- Có thể ghi trên thiết bị, đĩa cục bộ, Server (SysLog) hoặc kết hợp.
- Phải được lưu trữ trong thời gian dài và bảo quản cẩn thận.
- Khi sự cố xảy ra mới kiểm tra log là **đã quá muộn** → cần giám sát chủ động.

> **📌 Cập nhật 2026:**
> - **SIEM (Security Information and Event Management)** như Splunk, IBM QRadar, Microsoft Sentinel đã thay thế việc xem log thủ công.
> - **SOAR (Security Orchestration, Automation and Response)** – Tự động hóa phản ứng với sự cố.
> - **XDR (Extended Detection and Response)** – Tích hợp phát hiện và phản ứng trên nhiều lớp (endpoint, network, cloud).
> - **Zero Trust Architecture** – Không tin tưởng mặc định bất kỳ thiết bị hay người dùng nào, kể cả trong mạng nội bộ. Luôn xác thực lại.

---

## BẢNG TÓM TẮT NHỮNG GÌ ĐÃ LỖI THỜI (2026)

| Nội dung trong bài | Tình trạng hiện tại |
|---|---|
| Boot virus | Gần như biến mất |
| Ethereal (sniffer) | Thay hoàn toàn bởi Wireshark |
| BackOrifice, NetBus, Subseven | Lỗi thời, không còn sử dụng |
| PAP | Không dùng trong môi trường hiện đại |
| CHAP/MD5 | Yếu, đang bị thay thế bởi MFA |
| Jolt2, Targa, Bubonic.c (DoS tools) | Không còn phổ biến |
| Worm kiểu cũ (Mellisa, Blaster…) | Thay bằng Ransomware, Fileless Malware |
| Macro virus truyền thống | Giảm mạnh sau Microsoft chặn macro 2022 |
| Xem log thủ công | Thay bằng SIEM, SOAR, XDR |

---

## XU HƯỚNG NỔI BẬT 2024–2026

| Xu hướng | Mô tả |
|---|---|
| **Ransomware as a Service** | Nhóm tội phạm cho thuê ransomware, tấn công quy mô lớn |
| **AI trong An ninh mạng** | AI tấn công (deepfake, phishing tinh vi) và phòng thủ (phát hiện bất thường) |
| **Zero Trust Architecture** | Không tin tưởng mặc định bất kỳ ai, kể cả trong mạng nội bộ |
| **Supply Chain Attack** | Tấn công nhà cung cấp phần mềm để lan rộng đến hàng nghìn nạn nhân |
| **Cloud Security** | Bảo mật hạ tầng đám mây (AWS, Azure, GCP) trở thành kỹ năng thiết yếu |
| **IoT Security** | Hàng tỷ thiết bị IoT bảo mật yếu là mục tiêu botnet DDoS |
| **Passwordless / FIDO2** | Xác thực không mật khẩu, thay thế dần username/password truyền thống |
| **Post-Quantum Cryptography** | Chuẩn bị cho máy tính lượng tử phá vỡ RSA/ECC, NIST đang chuẩn hóa thuật toán mới |
| **MFA** | Xác thực đa yếu tố trở thành tiêu chuẩn bắt buộc |
| **SIEM / SOAR / XDR** | Tự động hóa giám sát và phản ứng sự cố |

---

*Tài liệu tổng hợp từ slide bài giảng Chương 1 – An Toàn Hệ Thống và An Ninh Mạng, cập nhật xu hướng đến 2026.*
