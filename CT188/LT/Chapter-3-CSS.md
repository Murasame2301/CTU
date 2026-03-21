# CSS

## CSS

### Định nghĩa CSS

### Cú pháp CSS
### Cách thêm CSS:
Có 3 phương pháp chính: Inline, Internal, External.
## Các loại bộ chọn CSS
### Bộ chọn cơ bản (Basic Selectors)
Có 5 Bộ Chọn Cơ Bản:
  + **Type selector**: Sử dụng tên thẻ (như p, h1) để chọn tất cả các phần tử cùng loại.
  + **Class selector**: Sử dụng dấu chấm (.) trước tên lớp để chọn nhóm phần tử có cùng thuộc tính class.
  + **ID selector**: Sử dụng dấu thăng (#) trước tên danh hiệu để chọn duy nhất một phần tử có id tương ứng.
  + **Universal selector**: Sử dụng dấu sao (*) để khớp với mọi phần tử HTML.
  + **Selector list**: Gom nhóm các bộ chọn có cùng khối khai báo bằng dấu phẩy
### Bộ chọn thuộc tính (Attribute selectors):
Chọn các phần tử dựa trên sự hiện diện hoặc giá trị của thuộc tính (ví dụ: [type="text"])
### Bộ chọn kết hợp (Combinators):
Chọn các phần tử dựa trên mối quan hệ giữa chúng, bao gồm: hậu duệ (khoảng cách), con trực hệ (>), anh em kề nhau (+), và anh em kế tiếp (~)
### Bộ chọn lớp giả (Pseudo-classes) và phần tử giả (Pseudo-elements):
- Lớp giả (:) dùng để định kiểu trạng thái cụ thể (như :hover, :active)
- Phần tử giả (::) dùng để định kiểu một phần cụ thể của phần tử (như ::first-line, ::after)
### Bộ chọn lồng nhau (& nesting selector): 
Được sử dụng để giảm việc lặp lại tên bộ chọn cha trong ngữ cảnh có liên kết cha-con.
## Cơ chế xếp tầng và Độ cụ thể (Selector Specificity)
- **Độ cụ thể** là giá trị dùng để xác định mức độ ưu tiên của các bộ chọn khi xảy ra xung đột thuộc tính trong cùng một nguồn CSS

- Giải thuật tính độ cụ thể (A, B, C): Trình duyệt so khớp dựa trên ba thành phần theo thứ tự ưu tiên từ A đến C:
  + **A (ID-like)**: Số lượng bộ chọn ID (trọng số 100)
  + **B (Class-like)**: Số lượng bộ chọn lớp, thuộc tính và lớp giả (trọng số 10)
  + **C (Element-like)**: Số lượng bộ chọn phần tử và phần tử giả (trọng số 1)
**Thứ tự ưu tiên từ cao đến thấp:**
1. **!important**: Có ưu tiên cao nhất (vô hạn), nhưng không khuyến khích sử dụng
2. **Inline style (Kiểu nội tuyến)**: Trọng số 1000
3. **ID**: Trọng số 100
4. **Class / Attribute / Pseudo-class**: Trọng số 10
5. **Element / Pseudo-element**: Trọng số 1
6. **Universal selector (*)**: Có độ cụ thể bằng 0
## Tính thừa kế (Inheritance)
- **Thuộc tính được thừa kế (Inherited property)**: Là những thuộc tính mà **giá trị được tính toán (computed value)** của phần tử cha sẽ tự động được truyền cho phần tử con
  + Ví dụ tiêu biểu nhất là thuộc tính color
  + Ngoài ra, font-size cũng là một thuộc tính có tính thừa kế
- **Thuộc tính không được thừa kế (Non-inherited property)**: Các thuộc tính này không nhận giá trị từ cha. Thay vào đó, phần tử con sẽ sử dụng giá trị ban đầu (initial value) của thuộc tính đó
  + Một ví dụ điển hình là thuộc tính border

- **Các từ khóa toàn cục (Global keywords):** có thể điều khiển tính thừa kế một cách thủ công bằng các từ khóa sau:
  + inherit: Ép buộc một thuộc tính phải kế thừa giá trị từ phần tử cha
  + initial: Thiết lập thuộc tính về giá trị mặc định ban đầu của trình duyệt
  + unset: Nếu thuộc tính có tính kế thừa tự nhiên, nó sẽ hoạt động như inherit; nếu không, nó sẽ hoạt động như initial

## Đơn vị đo lường
- **Đơn vị tuyệt đối (Absolute length units)** có độ dài cố định và không thay đổi theo kích thước phần tử cha:
  + **px (Pixels)**: Bằng 1/96 inch (là đơn vị tuyệt đối trong CSS3)
  + **cm, mm, in**: Centimeters, Millimeters và Inches
  + **pt (Points), pc (Picas)**: Các đơn vị thường dùng trong in ấn
- **Đơn vị tương đối (Relative length units)** có độ dài thay đổi theo kích thước phần tử cha hoặc khung nhìn (viewport), rất quan trọng trong thiết kế linh hoạt và đáp ứng (Responsive layout)
  + **%**: Tính theo tỷ lệ phần trăm so với phần tử cha
  + **em**: Dựa trên kích thước font hiện hành hoặc của phần tử cha
  + rem: Tương tự em nhưng so với phần tử gốc (root)
  + **vh, vw**: Tương ứng với 1% chiều cao hoặc chiều rộng của khung nhìn trình duyệt
  + **vmin, vmax**: Lấy giá trị nhỏ nhất hoặc lớn nhất giữa vh và vw
  + **ex, ch**: Dựa trên chiều cao chữ "x" thường hoặc chiều rộng của ký số "0" của font hiện hành
## Box Model
### Các thành phần của Box Model
- Gồm 4 thành phần chính:
  + **Content (Nội dung)**: Phần chứa văn bản hoặc hình ảnh, được xác định bởi thuộc tính width và height
  + **Padding (Vùng đệm)**: Khoảng không gian bao quanh nội dung, phần này có tính chất trong suốt
  + **Border (Đường viền)**: Lớp khung bao quanh vùng đệm và nội dung
  + **Margin (Lề)**: Khoảng cách ngoài cùng giữa phần tử này với phần tử khác, cũng có tính chất trong suốt
- Mỗi thành phần trên đều có 4 phía: top, right, bottom, left.
### Cách tính kích thước phần tử:
- **Tổng độ rộng nhìn thấy (Visible width)**: border-left + padding-left + width + padding-right + border-right
- **Tổng độ rộng chiếm dụng (Entire width)**: Bao gồm tổng độ rộng nhìn thấy cộng thêm phần margin trái và phải
### Thuộc tính box-sizing:
- **content-box (mặc định)**: Kích thước width và height chỉ áp dụng cho phần nội dung. Nếu thêm padding và border, phần tử sẽ to ra.
- **border-box**: Kích thước width và height đã bao gồm cả padding và border. Cách này giúp lập trình viên dễ dàng tính toán bố cục layout hơn
### Các hành vi đặc biệt:
- **Display (Kiểu hiển thị)**: Mỗi thành phần của Box Model chịu chi phối bởi thuộc tính display (như `inline`, `block`, `inline-block`). Ví dụ, phần tử inline không có tác dụng với thuộc tính `width`/`height`.
- **Margin collapse (Thu gọn lề):**: Khi hai phần tử `block` đặt cạnh nhau theo chiều dọc, lề trên và dưới của chúng sẽ xảy ra hiện tượng thu gọn vào nhau thay vì cộng dồn

## Định vị (Positioning)
-> là phương pháp giúp đặt phần tử vào một vị trí cụ thể trên trang web thay vì tuân theo luồng thông thường (Normal flow). Sau khi thiết lập thuộc tính position, vị trí thực tế của phần tử sẽ được chỉ định bằng các độ dời (offset values) thông qua bốn thuộc tính: left, right, top, bottom
- Các kiểm định vị chính:
  + **Static (Định vị tĩnh)**: Đây là kiểu mặc định, phần tử xuất hiện theo luồng thông thường và bỏ qua các thuộc tính độ dời
  + **Relative (Định vị tương đối)**: Phần tử được dời đi so với vị trí ban đầu của chính nó, trong khi phần khoảng trống cũ của nó vẫn được bảo toàn trên trang
  + **Absolute (Định vị tuyệt đối)**: Phần tử được định vị dựa trên Khối chứa (Containing block) của nó, thường là tổ tiên gần nhất có kiểu định vị khác static hoặc là khung nhìn (Viewport)
  + **Fixed (Định vị cố định)**: Phần tử luôn giữ nguyên vị trí so với khung nhìn trình duyệt, không thay đổi ngay cả khi người dùng cuộn trang
  + **Sticky (Định vị dính)**: Là sự kết hợp giữa relative và fixed; phần tử sẽ hoạt động như định vị tương đối cho đến khi đạt tới một vị trí xác định trong khung nhìn thì sẽ "bám dính" lại đó

- **z-index:**
## Bố cục (Layout) và RWD
### Các loại bố cục (CSS Layouts)
Hiện nay có ba loại bố cục phổ biến được sử dụng:
- **Float layout (CSS 2.1):** Sử dụng thuộc tính `float` kết hợp với kỹ thuật **Clearfix** để xử lý các dị thường khi phần tử trôi lên lấp khoảng trống.
- **Flexbox layout (CSS3):** Là bố cục **một chiều**, dùng để sắp xếp các mục dọc theo một trục (trục chính) ³. Các phần tử con (flex items) có khả năng tự động co giãn để lấp đầy không gian của phần tử cha (flex container).
- **Grid layout (CSS3):** Là bố cục **hai chiều**, cung cấp hệ thống dàn trang theo cả hàng và cột.
### Thiết kế web đáp ứng (RWD)
**RWD (Responsive Web Design)** là phương pháp giúp trang web thích ứng và hiển thị hiệu quả trên nhiều kích thước màn hình và độ phân giải khác nhau (web đa thiết bị).
Các khái niệm quan trọng:
- **Nguyên tắc thiết kế:** Chỉ cần 1 phiên bản duy nhất cho mọi thiết bị, đảm bảo trải nghiệm người dùng nhất quán thông qua chiến lược **Desktop-First** hoặc **Mobile-First**.
- **Truy vấn phương tiện (CSS Media Query):** Cho phép thay đổi bố cục dựa trên kích thước khung nhìn (viewport). Cú pháp thường gồm kiểu phương tiện (như `screen`), toán tử logic (`and`, `not`) và các tính năng như `width` hoặc `orientation`.
- **Breakpoint (Điểm ngắt):** Là các mốc chiều rộng màn hình cụ thể (ví dụ: 480px, 768px, 1024px) mà tại đó bố cục sẽ thay đổi để tối ưu hóa việc hiển thị.
- **RWD không cần Media Queries:** Các kỹ thuật CSS hiện đại như Grid và Flexbox cho phép nội dung tự điều chỉnh theo viewport bằng các hàm như `minmax()` hay `auto-fit` mà không nhất thiết phải thiết lập điểm ngắt thủ công.
