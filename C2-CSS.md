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
## Box Model
## Định vị (Positioning)
## Bố cục (Layout) và RWD
