# 📡 CHƯƠNG 2: AN TOÀN CHO CÁC THIẾT BỊ MẠNG

---

## I) Tầng 1 (Physical Layer)

### Khái niệm
> **Điểm truy nhập (Access Point)** là nơi người dùng hợp lệ *và không hợp lệ* có thể truy cập vào mạng để khai thác tài nguyên.

Tầng vật lý quan tâm đến **phương tiện truyền dẫn** – nơi tín hiệu đi qua. Kẻ tấn công ở tầng này thường tấn công **trực tiếp vào đường cáp hoặc sóng**.

---

### Cáp đồng trục
Có **3 cách nghe lén**:

| Cách | Kỹ thuật | Khả năng phát hiện |
|------|----------|-------------------|
| 1 | Gắn **T-connector** trực tiếp | ✅ Dễ phát hiện (gián đoạn mạng) |
| 2 | Dùng **Vampire Tap** xuyên vỏ bọc | ⚠️ Khó phát hiện |
| 3 | Thiết bị **cảm ứng bao quanh** cáp | ❌ Không thể phát hiện |

**Hệ quả:** Cách 3 nguy hiểm nhất vì hoàn toàn bị động, không để lại dấu vết vật lý.

**Bảo vệ:** Cô lập đường cáp, không cho tiếp xúc trực tiếp.

---

### Cáp xoắn đôi (UTP/STP)
- Tấn công thường qua **switch hoặc patch-panel** (điểm tập trung kết nối).
- **Bảo vệ:** Tách riêng switch vào phòng quản trị, dùng **tủ có khóa**.

---

### Cáp quang
- **Tính chất:** Khó bị nghe lén trực tiếp vì truyền ánh sáng, không phải điện.
- **Điểm yếu:** Nằm ở **đầu nối (connector)** – có thể chèn **bộ chia (splitter)** để sao chép tín hiệu.
- **Hệ quả:** Vì cần bộ thu phát đi kèm nên dễ bị phát hiện hơn cáp đồng.

---

### Mạng không dây (WiFi – RF)
- **Tính chất:** Sóng radio lan rộng trong không gian → **bất kỳ ai trong vùng phủ sóng đều có thể nhận tín hiệu**.
- **Hệ quả:** Đây là môi trường truyền dẫn kém an toàn nhất ở tầng 1.
- **Bảo vệ:** Mã hóa bằng **WEP** (yếu hơn) hoặc **WPA** (mạnh hơn).

> 🔄 **Cập nhật 2026:**
> - **WEP** đã bị **phá hoàn toàn** từ lâu, không còn được sử dụng trong thực tế.
> - **WPA (WPA1)** cũng đã lỗi thời và dễ bị tấn công.
> - Chuẩn hiện tại là **WPA2** (phổ biến) và **WPA3** (2018, đang thay thế WPA2).
> - **WPA3** cải tiến lớn: dùng **SAE (Simultaneous Authentication of Equals)** thay cho PSK, chống tấn công brute-force và dictionary attack hiệu quả hơn.
> - Với mạng doanh nghiệp: dùng **WPA3-Enterprise** kết hợp **802.1X** và chứng chỉ số.

---

### Modem
- **Nguy cơ:** Kẻ tấn công dùng **War Dialer** – phần mềm tự động quét và gọi đến các số điện thoại để tìm modem kết nối máy tính.
- **Hệ quả:** Nếu tìm được modem → xâm nhập trực tiếp vào máy tính nội bộ, **vượt qua toàn bộ firewall**.
- **Bảo vệ:** Giới hạn dùng modem, chỉ cho phép **hướng gọi đi**.

> 🔄 **Cập nhật 2026:**
> - Dial-up Modem và War Dialer **gần như không còn phổ biến** trong môi trường doanh nghiệp hiện đại.
> - Thay vào đó, các mối đe dọa truy cập từ xa hiện nay tập trung vào **khai thác lỗ hổng VPN**, **tấn công RDP (Remote Desktop Protocol)** và **phishing để chiếm credential**.
> - Khuyến nghị hiện đại: thay VPN truyền thống bằng **ZTNA (Zero Trust Network Access)** để kiểm soát truy cập từ xa an toàn hơn.

---

## Phần 2 – Tầng 2 (Data Link Layer)

### Khái niệm
> Thiết bị tầng 2 đã có **"thông minh"** nhất định: nhận biết **địa chỉ MAC** và chuyển dữ liệu dựa trên địa chỉ vật lý này.

- **Switch an toàn hơn Hub** vì mỗi cổng chỉ nhận đúng dữ liệu của mình + broadcast.
- **Hệ quả:** Kẻ tấn công không thể đơn giản cắm vào mạng và nghe lén như với Hub.

---

### Tấn công Switch qua SPAN
- **SPAN (Switched Port Analyzer):** Tính năng quản trị dùng để **sao chép toàn bộ gói tin** từ một/nhiều cổng đến một cổng giám sát.
- **Hệ quả:** Nếu hacker chiếm được tài khoản admin switch → lợi dụng SPAN để **nghe lén toàn bộ lưu lượng mạng** dù đang dùng switch.
- *(3Com gọi tính năng này là RAP – Roving Analysis Port)*

---

### Tấn công ARP Spoofing (Giả mạo ARP)
**Khái niệm ARP:** Giao thức dùng để ánh xạ địa chỉ IP → địa chỉ MAC. Kết quả được lưu trong **ARP Cache**.

**Cơ chế tấn công:**
1. Kẻ tấn công gửi ARP giả đến **Client1**: "IP của Client2 có MAC là của tôi"
2. Đồng thời gửi ARP giả đến **Client2**: "IP của Client1 có MAC là của tôi"
3. **Hệ quả:** Cả hai client cập nhật ARP Cache sai → mọi dữ liệu trao đổi đều đi qua máy kẻ tấn công (**Man-in-the-Middle**) mà không ai hay biết.

---

### Wireless Access Point
- **Điểm yếu:** AP không mã hóa → ai trong vùng phủ sóng đều kết nối được, **không cần tài khoản**.
- **Bảo vệ:**
  - Ẩn **SSID**
  - Đặt key dài (**128-bit**), thường xuyên thay đổi
  - **Lọc MAC (MAC Filter):** chỉ cho phép thiết bị trong danh sách

> 🔄 **Cập nhật 2026:**
> - **Ẩn SSID** và **MAC Filter** chỉ là lớp bảo vệ phụ – kẻ tấn công có thể dễ dàng dò SSID ẩn bằng công cụ và giả mạo MAC address.
> - Biện pháp hiện đại hơn bao gồm:
>   - Dùng **WPA3** thay WPA2 để chống brute-force.
>   - **802.1X + RADIUS** cho mạng doanh nghiệp: mỗi người dùng có credential riêng.
>   - Triển khai **Wireless IDS/IPS** để phát hiện AP giả mạo (Rogue AP).
>   - Phân vùng mạng WiFi khách riêng biệt với mạng nội bộ (**Guest VLAN**).

---

## Phần 3 – Tầng 3 (Network Layer)

### Khái niệm
> Thiết bị tầng 3 hoạt động dựa trên **địa chỉ IP (địa chỉ logic)**, vạch đường cho gói tin và cung cấp nhiều cơ chế bảo mật hơn tầng dưới.

---

### Router
**Chức năng bảo mật của Router:**
- **ACL (Access Control List):** Lọc gói theo địa chỉ IP, cổng dịch vụ.
- **Lọc gói tin** theo loại/nội dung.
- **QoS:** Ưu tiên lưu lượng quan trọng.

**Điểm yếu:**
- **Telnet (cổng 23):** Truyền mật khẩu dạng **plain-text** → dễ bị nghe lén.
- **Dynamic Routing giả mạo:** Kẻ tấn công giả danh router, gửi thông tin định tuyến sai → **làm lệch hướng lưu lượng mạng**.
- **Bảo vệ:** Dùng giao thức định tuyến có mã hóa + xác thực.

> 🔄 **Cập nhật 2026:**
> - **Telnet hoàn toàn không còn được khuyến nghị** – thay bằng **SSH (Secure Shell)** để quản trị thiết bị từ xa có mã hóa.
> - Các router hiện đại hỗ trợ **quản trị qua HTTPS** thay HTTP.
> - Tấn công định tuyến hiện đại còn nhắm vào **BGP Hijacking** – chiếm đoạt các khối địa chỉ IP trên Internet, phổ biến ở quy mô ISP/quốc gia.
> - Bảo vệ BGP: dùng **RPKI (Resource Public Key Infrastructure)** để xác thực thông tin định tuyến.

---

### RAS – Remote Access Server (Máy chủ truy cập từ xa)
**Khái niệm:** Cung cấp kết nối cho người dùng từ xa qua **dial-up** hoặc **VPN**.

Các giao thức xác thực, từ **yếu → mạnh**:

| Giao thức | Cơ chế | Mức độ an toàn |
|-----------|--------|---------------|
| **PAP** | Truyền mật khẩu plain-text | ❌ Không an toàn |
| **SPAP** | Có mã hóa | ⚠️ Khá hơn PAP |
| **CHAP / MS-CHAP** | Mã hóa, **không truyền mật khẩu** trực tiếp | ✅ An toàn |
| **EAP** | Kết hợp smartcard, sinh trắc học | ✅✅ Rất an toàn |
| **RADIUS** | Xác thực tập trung client/server | ✅✅✅ Tốt nhất |

**RADIUS – tính chất nổi bật:**
- Mô hình **client/server** tập trung.
- Hỗ trợ nhiều kiểu xác thực (PAP, CHAP...).
- **Một cơ sở dữ liệu duy nhất** quản lý toàn bộ xác thực → dễ quản lý, nhất quán.

> 🔄 **Cập nhật 2026:**
> - **PAP và SPAP** đã bị loại bỏ hoàn toàn khỏi các hệ thống hiện đại.
> - **MS-CHAPv2** (dùng trong PPTP VPN) cũng đã bị phá – không còn an toàn.
> - **RADIUS** vẫn dùng rộng rãi nhưng đang được nâng cấp lên **RadSec (RADIUS over TLS)** để mã hóa toàn bộ phiên xác thực.
> - Xu hướng hiện đại: xác thực dựa trên **MFA (Multi-Factor Authentication)**, **FIDO2 / Passkey** (không cần mật khẩu), và tích hợp với **Identity Provider (IdP)** như Azure AD, Okta.
> - **VPN truyền thống** đang được thay thế dần bởi **ZTNA (Zero Trust Network Access)**: thay vì mở toàn bộ mạng cho người dùng, chỉ cho phép truy cập đúng ứng dụng cần thiết.

**Mandatory Callback:**
- Sau xác thực thành công, **server gọi lại client** theo số điện thoại định trước.
- **Hệ quả:** Dù kẻ tấn công biết mật khẩu cũng không thể kết nối từ số lạ.
- **Hạn chế:** Chỉ phù hợp **người dùng cố định** (không dùng được khi đi công tác).

---

### Firewall tầng 3 (Lọc gói – Packet Filtering)
**Khái niệm:** Kiểm tra **header** của gói tin, cho phép/từ chối dựa trên địa chỉ IP và cổng.

**2 chính sách:**
- **Allow by default:** Cho phép tất cả, chặn những gì bị cấm → **kém an toàn**
- **Deny by default:** Chặn tất cả, chỉ mở những gì cần → ✅ **Chính sách tốt hơn**

**Ưu điểm:**
- Tốc độ nhanh (chỉ đọc header)
- Trong suốt với người dùng
- Dễ cấu hình

**Hạn chế:**
- **Không kiểm tra nội dung gói** → bỏ sót mã độc ẩn trong payload ⚠️
- Khó mở cổng linh hoạt cho từng ứng dụng

**3 loại Firewall tổng quát:**

| Loại | Tầng hoạt động |
|------|---------------|
| Lọc gói | Tầng 3 |
| Lọc nội dung | Tầng ứng dụng |
| Duyệt trạng thái (Stateful) | Tất cả các tầng |

> 🔄 **Cập nhật 2026:**
> - Firewall lọc gói đơn thuần **hầu như không còn dùng độc lập** trong môi trường doanh nghiệp.
> - Thế hệ hiện tại là **NGFW (Next-Generation Firewall)** tích hợp nhiều tính năng:
>   - **DPI (Deep Packet Inspection):** kiểm tra toàn bộ nội dung gói, kể cả payload.
>   - **IPS (Intrusion Prevention System):** phát hiện và chặn tấn công theo thời gian thực.
>   - **Application Awareness:** nhận diện ứng dụng (không chỉ dựa theo cổng).
>   - **TLS Inspection:** giải mã và kiểm tra lưu lượng HTTPS.
>   - **AI/ML-based threat detection:** phát hiện mối đe dọa dựa trên hành vi bất thường.
> - Ngoài ra, mô hình **Zero Trust** không còn tin tưởng bất kỳ thiết bị nào trong mạng nội bộ – mọi truy cập đều phải xác thực lại.

---

## Phần 4 – Tầng 4 trở lên

### Khái niệm
> Tầng 4 trở lên là nơi **hệ điều hành và ứng dụng** hiện diện → cần bảo mật riêng cho từng hệ thống.

---

### Proxy Server
**Khái niệm:** Đứng giữa mạng nội bộ và Internet, thay mặt client gửi yêu cầu ra ngoài.

**Tính chất:**
- **Cache** → tăng tốc truy cập web
- **Lưu log** → giám sát lưu lượng
- **Lọc** theo giao thức, địa chỉ
- **Che giấu** địa chỉ IP nội bộ

**Điểm yếu:** Nếu proxy server kiêm nhiệm nhiều chức năng khác → mỗi dịch vụ thêm là một lỗ hổng tiềm ẩn.

**Bảo vệ:** Dùng **server chuyên dụng** chỉ làm Proxy/Firewall.

---

### Máy trạm (Workstation)
**Tính chất:** Kém an toàn hơn server, thường bị bỏ qua → **mục tiêu dễ tấn công**.

**Điểm yếu:**
- Giao thức TCP/IP vốn không an toàn
- Dịch vụ chia sẻ file Windows dễ bị khai thác
- **Người dùng** thường tự tạo lỗ hổng: không đổi mật khẩu, cài phần mềm lạ, mở file đính kèm không rõ nguồn...

**Bảo vệ:** Tắt dịch vụ không cần, cài firewall, cập nhật antivirus, có chính sách sử dụng rõ ràng.

> 🔄 **Cập nhật 2026:**
> - **Ransomware** là mối đe dọa hàng đầu nhắm vào máy trạm – mã hóa toàn bộ dữ liệu và đòi tiền chuộc.
> - **Phishing và Social Engineering** ngày càng tinh vi (deepfake, AI-generated emails) → người dùng là điểm yếu lớn nhất.
> - **EDR (Endpoint Detection & Response)** thay thế antivirus truyền thống: giám sát hành vi thời gian thực thay vì chỉ quét chữ ký virus.
> - Khuyến nghị bổ sung: bật **MFA** cho tất cả tài khoản, áp dụng nguyên tắc **Least Privilege** (chỉ cấp đúng quyền cần thiết).

---

### Máy chủ (Server)
**Tính chất:** Mục tiêu hấp dẫn nhất vì chứa dữ liệu quan trọng.

**Hệ quả:** Server càng nhiều chức năng → càng nhiều bề mặt tấn công.

**Bảo vệ:**
- Đặt sau **một hoặc nhiều Firewall**
- Có lớp **bảo vệ vật lý**
- Thường xuyên cập nhật OS, ứng dụng, antivirus

> 🔄 **Cập nhật 2026:**
> - Nhiều tổ chức đã chuyển hạ tầng lên **Cloud (AWS, Azure, GCP)** → server vật lý giảm nhưng bảo mật **cloud configuration** trở thành điểm yếu mới (misconfiguration là nguyên nhân hàng đầu của data breach).
> - **Tấn công chuỗi cung ứng (Supply Chain Attack):** nhắm vào phần mềm/thư viện bên thứ ba mà server đang dùng (ví dụ: vụ SolarWinds 2020).
> - **Zero Trust cho Server:** mọi kết nối đến server đều phải xác thực, kể cả từ trong mạng nội bộ – không còn khái niệm "tin tưởng vì đang trong mạng".
> - Công cụ bảo vệ hiện đại: **SIEM (Security Information and Event Management)** để giám sát log tập trung, **WAF (Web Application Firewall)** cho các web server.

---

## 🎯 Bảng tổng hợp điểm yếu & biện pháp bảo vệ

| Thiết bị / Tầng | Điểm yếu chính | Biện pháp cũ (tài liệu) | Cập nhật 2026 |
|----------------|---------------|------------------------|--------------|
| Cáp đồng trục | Vampire tap, cảm ứng bao quanh | Cô lập vật lý | Vẫn còn nguyên giá trị |
| Cáp quang | Đầu nối (connector) | Giám sát splitter | Vẫn còn nguyên giá trị |
| WiFi | Sóng RF lan rộng | WEP / WPA | **WPA3**, 802.1X, Guest VLAN |
| Modem | War Dialer | Chỉ cho gọi đi | Thay bằng **ZTNA**, chống tấn công RDP/VPN |
| Switch | SPAN, ARP Spoofing | Bảo vệ tài khoản admin | Thêm **Dynamic ARP Inspection**, port security |
| Router | Telnet, Dynamic Routing giả | Mã hóa định tuyến | Thay Telnet bằng **SSH**, dùng **RPKI** chống BGP Hijacking |
| RAS | PAP plain-text | CHAP / EAP / RADIUS | **MFA, FIDO2, RadSec, ZTNA** |
| Firewall L3 | Không đọc nội dung gói | Stateful Firewall | **NGFW + IPS + DPI + AI detection** |
| Proxy | Kiêm nhiệm nhiều vai | Server chuyên dụng | Thêm **WAF** cho web server |
| Workstation | Người dùng thiếu ý thức | Antivirus, chính sách | **EDR, MFA, Least Privilege**, chống Ransomware |
| Server | Nhiều dịch vụ = nhiều lỗ hổng | Firewall + bảo vệ vật lý | **Zero Trust, SIEM, WAF**, bảo mật Cloud config |

---

## 🆕 Tóm tắt xu hướng bảo mật mạng 2026

| Khái niệm | Ý nghĩa |
|-----------|---------|
| **Zero Trust** | Không tin tưởng mặc định bất kỳ ai/thiết bị nào, kể cả trong mạng nội bộ |
| **ZTNA** | Zero Trust Network Access – thay thế VPN truyền thống |
| **NGFW** | Next-Generation Firewall – tích hợp DPI, IPS, AI |
| **EDR** | Endpoint Detection & Response – thay thế antivirus truyền thống |
| **MFA / FIDO2** | Xác thực đa yếu tố / xác thực không mật khẩu |
| **RadSec** | RADIUS over TLS – mã hóa toàn bộ phiên xác thực |
| **SIEM** | Giám sát và phân tích log bảo mật tập trung |
| **WAF** | Web Application Firewall – bảo vệ ứng dụng web |
| **RPKI** | Xác thực thông tin định tuyến BGP |
